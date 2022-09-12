//ForeFront electronics 2021

#pragma once

#include "Modules/ModuleManager.h"

class JWTPLUGIN_API FJWTPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
