#pragma once

#include <memory>					         //Memory Class

#include "Window.h"							 //Window Class
#include "Tiny/Events/Event.h"				 //Event Class
#include "Tiny/Events/ApplicationEvent.h"
#include "Tiny/Core/Layer.h"				 //Layer Class
#include "Tiny/Core/LayerStack.h"			 //LayerStack Class
#include "Tiny/ImGui/ImGuiLayer.h"

namespace Tiny {

	class Application
	{
	public:
		Application();
		Application(const char* title, uint32_t width, uint32_t hight);
		virtual ~Application();
	
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);

		void ExitApplication() { m_Running = false; }

		ImGuiLayer* GetImGuiLayer() { return m_imGuiLayer; }
		inline Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *m_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		Scope<Window> m_Window;
		bool m_Running = true;
		float m_lastTimestep = 0.0f;
		bool m_Minimized = false;

		LayerStack m_LayerStack;

		ImGuiLayer* m_imGuiLayer;
		
		static Application* m_Instance;

	};

	//To do defined in CLIENT 
	Application* CreateApplication();


}

