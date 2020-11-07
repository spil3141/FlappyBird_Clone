#pragma once

//----------------------------------------
// OpenGL    GLSL      GLSL
// version   version   string
//----------------------------------------
//  2.0       110       "#version 110"
//  2.1       120       "#version 120"
//  3.0       130       "#version 130"
//  3.1       140       "#version 140"
//  3.2       150       "#version 150"
//  3.3       330       "#version 330 core"
//  4.0       400       "#version 400 core"
//  4.1       410       "#version 410 core"
//  4.2       420       "#version 410 core"
//  4.3       430       "#version 430 core"
//  ES 2.0    100       "#version 100"      = WebGL 1.0
//  ES 3.0    300       "#version 300 es"   = WebGL 2.0
//----------------------------------------

/*
* Macros 
*/
#ifdef T_PLATFORM_WINDOWS
	#ifdef T_DLLBUILD //Using T_DLLBUILD define when connecting a dll
		#ifdef T_BUILD_DLL
			#define T_API __declspec(dllexport)
		#else
			#define T_API __declspec(dllimport)
		#endif
	#else
		#define T_API 
	#endif
#else 
	#error Only windows is supported!
#endif

#ifdef TINY_ENABLE_ASSERTS
	#define T_ASSERT(x,...) { if(x) {  } else { T_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }  } 
	#define T_CORE_ASSERT(x,...) { if(x) {  } else { T_CORE_ERROR("Tiny Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else 
#define T_ASSERT(x,...)  // Do Nothing 
#define T_CORE_ASSERT(x,...) // Do Nothing 
#endif

//Event System Related Macros
#define BIT(x) (1 << x)
#define T_BIND_EVENT_FN(x) std::bind(x,this,std::placeholders::_1)


//#define T_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

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
