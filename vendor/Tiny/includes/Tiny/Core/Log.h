#pragma once

#include <memory>		//shared_ptr
#include "spdlog/spdlog.h"
#include "spdlog/spdlog.h"

namespace Tiny {
	
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
#ifdef T_DEBUG
	//Core macro
	#define T_CORE_TRACE(...)     ::Tiny::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define T_CORE_INFO(...)      ::Tiny::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define T_CORE_WARNING(...)   ::Tiny::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define T_CORE_ERROR(...)     ::Tiny::Log::GetCoreLogger()->error(__VA_ARGS__)
							  
	//Client macro				  
	#define T_TRACE(...)   ::Tiny::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define T_INFO(...)    ::Tiny::Log::GetClientLogger()->info(__VA_ARGS__)
	#define T_WARNING(...) ::Tiny::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define T_ERROR(...)   ::Tiny::Log::GetClientLogger()->error(__VA_ARGS__)
#else
	//Core macro
	#define T_CORE_TRACE(...)      
	#define T_CORE_INFO(...)       
	#define T_CORE_WARNING(...)    
	#define T_CORE_ERROR(...)      

	//Client macro				  
	#define T_TRACE(...)    
	#define T_INFO(...)     
	#define T_WARNING(...)  
	#define T_ERROR(...)    
#endif