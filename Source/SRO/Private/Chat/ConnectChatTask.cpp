﻿#include "Chat/ConnectChatTask.h"

#include "Util/SROWebLibrary.h"

void FConnectChatTask::DoWork()
{
	std::string host = TCHAR_TO_UTF8(*USROWebLibrary::GetChatGRPCUrl());
	const std::shared_ptr Channel = CreateChannel(host, grpc::InsecureChannelCredentials());
	std::unique_ptr Stub = ChatService::NewStub(Channel);

	CompletionQueue cq;
	ClientContext Context;
	Context.set_wait_for_ready(true);
	Context.AddMetadata("authorization", "Bearer " + std::string(TCHAR_TO_UTF8(*AuthToken)));
	Context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(5));

	std::unique_ptr<grpc::ClientAsyncReader<ChatMessage>> Reader;

	if (ChannelId == 0)
	{
		google::protobuf::Empty Empty;
		Reader = Stub->AsyncConnectDirectMessage(&Context, Empty, &cq, (void*)1);
	}
	else
	{
		ChannelIdMessage Request;
		Request.set_channel_id(1);
		Reader = Stub->AsyncConnectChannel(&Context, Request, &cq, (void*)1);
	}

	void* got_tag;
	bool ok = false;
	
	grpc::Status Status;
	Reader->Finish(&Status, (void*)10);
	cq.Next(&got_tag, &ok);
	if (ok && got_tag == (void*)10)
	{
		FString ErrorMessage(Status.error_message().c_str());
		FString ErrorDetails(Status.error_details().c_str());

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,
		                                 FString::Printf(TEXT("Error [%d] | %s : %s"),
		                                                 Status.error_code(),
		                                                 *ErrorMessage,
		                                                 *ErrorDetails));
	}
	return;

	// bool ret = cq.Next(&got_tag, &ok);
	// if (ret && ok && got_tag == (void*)1)
	// {
	// 	ChatMessage ChatMessage;
	// 	while (1)
	// 	{
	// 		Reader->Read(&ChatMessage, (void*)3);
	// 		ret = cq.Next(&got_tag, &ok);
	// 		if (!ret || !ok || got_tag != (void*)3)
	// 		{
	// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Chat Connection Closed");
	// 			break;
	// 		}
	//
	// 		FChatMessageStruct Message{FString(ChatMessage.username().c_str()), ChatMessage.message().c_str()};
	// 		if (Delegate && Delegate->IsBound())
	// 		{
	// 			Delegate->Broadcast(Message, ChannelId);
	// 		}
	// 	}
	// }
	//
	//
	// grpc::Status Status;
	// Reader->Finish(&Status, (void*)10);
	// ret = cq.Next(&got_tag, &ok);
	// if (ret && ok && got_tag == (void*)10)
	// {
	// 	FString ErrorMessage(Status.error_message().c_str());
	// 	FString ErrorDetails(Status.error_details().c_str());
	//
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,
	// 	                                 FString::Printf(TEXT("Error [%d] | %s : %s"),
	// 	                                                 Status.error_code(),
	// 	                                                 *ErrorMessage,
	// 	                                                 *ErrorDetails));
	// }
}