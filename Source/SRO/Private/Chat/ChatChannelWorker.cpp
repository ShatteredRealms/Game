#include "Chat/ChatChannelWorker.h"

#include "SRO/SRO.h"
#include "../../../../Intermediate/ProjectFiles/ThirdParty/grpc/include/grpcpp/create_channel.h"
#include "Util/SROWebLibrary.h"

#pragma region Main Thread Code

FChatChannelWorker::FChatChannelWorker(int64 _channelId,
                                       FString _characterName,
                                       FString _authToken) :
	ChannelId(_channelId),
	AuthToken(_authToken),
	CharacterName(_characterName),
	bRunThread(true)
{
	Thread = FRunnableThread::Create(this, TEXT("ChatChannel"));
}

FChatChannelWorker::~FChatChannelWorker()
{
	if (Thread)
	{
		Thread->Kill();
		delete Thread;
	}
}
#pragma endregion


bool FChatChannelWorker::Init()
{
	return true;
}

uint32 FChatChannelWorker::Run()
{

	while (bRunThread)
	{
		// Connect to the server
		ConnectServer();

		// Connection lost, broadcast event
		ChatConnectedEvent.Broadcast();

		// Exit if max retries is reached. Set max retries to -1 to disable.
		if (CurrentRetries == MaxRetries)
		{
			return 1;
		}

		// If we're going to run again, sleep
		if (bRunThread)
		{
			FPlatformProcess::Sleep(SleepAmountBetweenTries);
			CurrentRetries++;
		}
	}

	return 0;
}

void FChatChannelWorker::Stop()
{
	bRunThread = false;
}

void FChatChannelWorker::ConnectServer() 
{
	const std::string host = TCHAR_TO_UTF8(*USROWebLibrary::GetChatGRPCUrl());
	const std::shared_ptr Channel = CreateChannel(host, grpc::InsecureChannelCredentials());
	const std::unique_ptr Stub = ChatService::NewStub(Channel);

	ClientContext Context;
	Context.AddMetadata("authorization", "Bearer " + std::string(TCHAR_TO_UTF8(*AuthToken)));
	CompletionQueue cq;
	std::unique_ptr<grpc::ClientAsyncReader<ChatMessage>> Reader;

	if (ChannelId == 0)
	{
		sro::chat::CharacterName CName;
		CName.set_character_name(TCHAR_TO_UTF8(*CharacterName));
		Reader = Stub->AsyncConnectDirectMessage(&Context, CName, &cq, (void*)1);
	}
	else
	{
		ChannelIdMessage Request;
		Request.set_channel_id(1);
		Reader = Stub->AsyncConnectChannel(&Context, Request, &cq, (void*)1);
	}

	void* got_tag;
	bool ok = false;

	bool ret = cq.Next(&got_tag, &ok);
	if (ret && ok && got_tag == (void*)1)
	{
		CurrentRetries = 0;
		ChatConnectedEvent.Broadcast();
		ChatMessage ChatMessage;
		while (bRunThread)
		{
			Reader->Read(&ChatMessage, (void*)3);
			ret = cq.Next(&got_tag, &ok);
			if (!ret || !ok || got_tag != (void*)3)
			{
				break;
			}

			FChatMessageStruct Message{FString(ChatMessage.character_name().c_str()), ChatMessage.message().c_str()};
			MessageReceivedEvent.Broadcast(Message, ChannelId);
		}
	}


	grpc::Status Status;
	Reader->Finish(&Status, (void*)10);
	ret = cq.Next(&got_tag, &ok);
	if (ret && ok && got_tag == (void*)10)
	{
		FString ErrorMessage(Status.error_message().c_str());
		FString ErrorDetails(Status.error_details().c_str());

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,
		                                 FString::Printf(TEXT("Error [%d] %s : %s"),
		                                                 Status.error_code(),
		                                                 *ErrorMessage,
		                                                 *ErrorDetails));

		UE_LOG(LogSRO, Warning, TEXT("Error [%d] %s : %s"), Status.error_code(), *ErrorMessage, *ErrorDetails);
	}
}
