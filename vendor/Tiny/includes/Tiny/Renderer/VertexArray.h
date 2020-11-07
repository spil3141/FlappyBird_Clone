#pragma once
#include "Tiny/Core/Core.h"

#include "Tiny/Renderer/Buffer.h"
#include <vector>

namespace Tiny {

	class VertexArray
	{
	public:
		~VertexArray() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& Quad_VertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& Quad_IndexBuffer) = 0;

		virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual Ref<IndexBuffer>& GetIndexBuffer() = 0;

		static Ref<VertexArray> Create();

	protected:
		uint32_t m_Renderer_ID;
	};
}

