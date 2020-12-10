#pragma once

#include "Tiny/Renderer/RendererAPI.h"

namespace Tiny {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}
