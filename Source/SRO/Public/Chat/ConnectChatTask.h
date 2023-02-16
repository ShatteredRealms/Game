#pragma once

#include "CoreMinimal.h"
#include "SROChatService.h"
#include "Async/AsyncWork.h"

class FConnectChatTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FConnectChatTask>;

	FConnectChatTask(int64 _channelId, FString _characterName, FString _authToken, FChatMessageReceivedDelegate* _delegate)
		: ChannelId(_channelId), CharacterName(_characterName), AuthToken(_authToken), Delegate(_delegate)
	{
	}

	int64 ChannelId;
	FString AuthToken;
	FString CharacterName;
	FChatMessageReceivedDelegate* Delegate;

	void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMyTask, STATGROUP_ThreadPoolAsyncTasks);
	}
};
