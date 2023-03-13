#pragma once

#include "tepch.h"

#ifdef TE_PLATFORM_WINDOWS

extern  TinyEngine::Application*  TinyEngine::CreateApplication();

int main() {

	TinyEngine::Log::Init();

	TE_CORE_WARN("Initiallized Log!");
	TE_INFO("APP hello");

	auto app = TinyEngine::CreateApplication();
	app->Run();
	delete  app;

}
#endif