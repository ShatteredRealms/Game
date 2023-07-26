// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CargoListener.h"
#include "Styling/SlateStyle.h"
#include "Modules/ModuleManager.h"

class FCargoModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command. */
	void PluginButtonActivate();

private:
	void RegisterMenus();

private:

	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<FSlateStyleSet> StyleActive;
	TSharedPtr<FSlateStyleSet> StyleInactive;
	FCargoListener* Listener = NULL;
};