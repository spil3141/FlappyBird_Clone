#include "Tiny.h"
#include "Tiny/Core/EntryPoint.h"
#include "GameMode.h"

class GameApp : public Tiny::Application
{
public:
	GameApp()
	{
		PushLayer(new GameMode());
	};

	~GameApp()
	{
	};
};


Tiny::Application* Tiny::CreateApplication()
{
	return new GameApp();
}

