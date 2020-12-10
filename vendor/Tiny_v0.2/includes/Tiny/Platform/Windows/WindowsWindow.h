#pragma once

#include "Tiny/Core/Window.h"


#include "glad/glad.h"
#include "GlFW/glfw3.h"		 //GLFWwindow

namespace Tiny {



	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();

		virtual void OnUpdate() override;

		virtual unsigned int GetWidth() const override  { return m_Data.m_Width; }
		virtual unsigned int GetHeight() const override { return m_Data.m_Height; };

		inline virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback;  }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData 
		{
			std::string Title;
			unsigned int m_Width, m_Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}


//TEMPORARY / should be Replace with OpenGL ErrorHandlingCallback 
//GLFW || Glad || OpenGL 
//Handling OpenGL Errors

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}