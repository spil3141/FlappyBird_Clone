#include "Tiny.h"
#include "Tiny/Core/EntryPoint.h"

#include "Game.h"

namespace GameScope {

	class GameApp : public Tiny::Application
	{
	public:
		GameApp()
		{
			PushLayer(new Game());
		};

		~GameApp()
		{
		};
	};

}

Tiny::Application* Tiny::CreateApplication()
{
	return new GameScope::GameApp();
}

