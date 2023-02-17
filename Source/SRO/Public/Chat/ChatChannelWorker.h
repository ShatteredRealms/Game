#pragma once

#include "CoreMinimal.h"
#include "SROChatService.h"

class SRO_API FChatChannelWorker : public FRunnable
{
	int64 ChannelId;
	FString AuthToken;
	FString CharacterName;

	DECLARE_EVENT_TwoParams(FChatChannelWorker, FChatMessageReceivedEvent, FChatMessageStruct, int64);
	FChatMessageReceivedEvent MessageReceivedEvent;

	DECLARE_EVENT(FChatChannelWorker, FChatConnectionUpdateEvent);
	FChatConnectionUpdateEvent ChatConnectionLostEvent;
	FChatConnectionUpdateEvent ChatConnectedEvent;

	int MaxRetries = -1;
	int CurrentRetries = 0;
	int SleepAmountBetweenTries = 5;

	FRunnableThread* Thread;
	bool bRunThread;



	void ConnectServer();

public:
	FChatChannelWorker(int64 _channelId,
	                   FString _characterName,
	                   FString _authToken);
	
	virtual ~FChatChannelWorker() override;
	
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	FChatConnectionUpdateEvent& OnChatConnectionLost() { return ChatConnectionLostEvent; }
	FChatConnectionUpdateEvent& OnChatConnected() { return ChatConnectedEvent; }
	FChatMessageReceivedEvent& OnChatMessageReceived() { return MessageReceivedEvent; }
};
