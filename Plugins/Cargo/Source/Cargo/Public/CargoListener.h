// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#define KBUSDFRONT

class FCargoListener : public FRunnable
{
public:

	FCargoListener();
	~FCargoListener();

	virtual uint32 Run() override;
	virtual void Stop() override;

private:

	FRunnableThread* ListenerThread = NULL;
};