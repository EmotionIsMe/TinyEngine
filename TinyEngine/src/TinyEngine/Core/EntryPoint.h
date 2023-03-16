#pragma once

#include "tepch.h"

#ifdef TE_PLATFORM_WINDOWS

extern  TinyEngine::Application*  TinyEngine::CreateApplication();

int main() {

	TinyEngine::Log::Init();

	TE_PROFILE_BEGIN_SESSION("Startup", "TinyEngineProfile-Startup.json");
	auto app = TinyEngine::CreateApplication();
	TE_PROFILE_END_SESSION();

	TE_PROFILE_BEGIN_SESSION("Runtime", "TinyEngineProfile-Runtime.json");
	app->Run();
	TE_PROFILE_END_SESSION();

	TE_PROFILE_BEGIN_SESSION("Startup", "TinyEngineProfile-Shutdown.json");
	delete app;
	TE_PROFILE_END_SESSION();

}
#endif