#pragma once

#include "tepch.h"
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace TinyEngine {

	class TE_API Log
	{
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>&	GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>&	GetClientLogger() { return s_ClientLogger; }
		
	private:
		
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		

	};
}

// Core log macros
#define TE_CORE_TRACE(...)	::TinyEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TE_CORE_INFO(...)	::TinyEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TE_CORE_WARN(...)	::TinyEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TE_CORE_ERROR(...)	::TinyEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TE_CORE_FATAL(...)	::TinyEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define TE_TRACE(...)		::TinyEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TE_INFO(...)		::TinyEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define TE_WARN(...)		::TinyEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TE_ERROR(...)		::TinyEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define TE_FATAL(...)		::TinyEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

