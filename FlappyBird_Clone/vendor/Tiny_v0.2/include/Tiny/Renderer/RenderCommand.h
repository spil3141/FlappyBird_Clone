#pragma once
#include "Tiny/Core/Core.h"
#include "Tiny/Renderer/RendererAPI.h"

namespace Tiny {

	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void Shutdown()
		{
			s_RendererAPI->Shutdown();
		}
		
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4 color = glm::vec4(0.1f, 0.1f, 0.1f, 0.1f))
		{
			s_RendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& VAO, uint32_t indexCount)
		{
			s_RendererAPI->DrawIndexed(VAO, indexCount);
		}
		
		static void DrawIndexed(const Ref<VertexArray>& VAO)
		{
			s_RendererAPI->DrawIndexed(VAO);
		}
	
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}

