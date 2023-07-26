// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class FCargoCommands : public TCommands<FCargoCommands>
{
public:

	FCargoCommands()
		: TCommands<FCargoCommands>(TEXT("Cargo"), NSLOCTEXT("Contexts", "Cargo", "Cargo Plugin"), NAME_None, FName("CargoStyle"))
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginActivate;
};
