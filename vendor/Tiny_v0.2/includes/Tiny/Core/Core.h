#pragma once

#include <memory.h> // for the smart pointers
#include "Tiny/Core/PlatformDetection.h"


/***********************************
* Tiny Macros 
************************************/

#ifdef T_DEBUG
	#if defined(T_PLATFORM_WINDOWS)
		#define T_DEBUGBREAK() __debugbreak()
	#elif defined(T_PLATFORM_LINUX)
		#include <signal.h>
		#define T_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define T_ENABLE_ASSERTS
#else
	#define HZ_DEBUGBREAK()
#endif
//
//#ifdef T_PLATFORM_WINDOWS
//	#ifdef T_DLLBUILD //Using T_DLLBUILD define when connecting a dll
//		#ifdef T_BUILD_DLL
//			#define T_API __declspec(dllexport)
//		#else
//			#define T_API __declspec(dllimport)
//		#endif
//	#else
//		#define T_API 
//	#endif
//#else 
//	#error Only windows is supported!
//#endif

#ifdef TINY_ENABLE_ASSERTS
	#define T_ASSERT(x,...) { if(x) {  } else { T_ERROR("Assertion Failed: {0}", __VA_ARGS__); T_DEBUGBREAK(); }  } 
	#define T_CORE_ASSERT(x,...) { if(x) {  } else { T_CORE_ERROR("Tiny Assertion Failed: {0}", __VA_ARGS__); T_DEBUGBREAK(); } }
#else 
	#define T_ASSERT(x,...)  // Do Nothing 
	#define T_CORE_ASSERT(x,...) // Do Nothing 
#endif

//Event System Related Macros
#define BIT(x) (1 << x)
//#define T_BIND_EVENT_FN(x) std::bind(x,this,std::placeholders::_1)
#define T_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }



namespace Tiny {
	//Generate and execute this function at Compile time. 
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
