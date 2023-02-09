#pragma once

#include "CoreMinimal.h"
#include "SROChatService.h"
#include "Async/AsyncWork.h"

class FConnectChatTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FConnectChatTask>;

	FConnectChatTask(int64 _channelId, FString _authToken, FChatMessageReceivedDelegate* _delegate)
		: ChannelId(_channelId), AuthToken(_authToken), Delegate(_delegate)
	{
	}

	int64 ChannelId;
	FString AuthToken;
	FChatMessageReceivedDelegate* Delegate;

	void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMyTask, STATGROUP_ThreadPoolAsyncTasks);
	}
};
