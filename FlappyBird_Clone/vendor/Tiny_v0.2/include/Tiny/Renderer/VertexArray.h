#pragma once
#include "Tiny/Core/Core.h"

#include "Tiny/Renderer/Buffer.h"
#include <memory>

namespace Tiny {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
	/*class VertexArray
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
	};*/
}

