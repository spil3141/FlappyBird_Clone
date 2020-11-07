#pragma once

#ifdef T_PLATFORM_WINDOWS

extern Tiny::Application* Tiny::CreateApplication();

//#include <iostream>

int main(int argc, char** argv)
{
	//Logging Initialization
	Tiny::Log::Init();
	T_CORE_INFO("Initialized Tiny!");
	//Begin the Application
	Tiny::Application* Application = Tiny::CreateApplication();
	Application->Run();
	delete Application;

	return 1;
}

#else
	#error Tiny Only Support Windows
#endif