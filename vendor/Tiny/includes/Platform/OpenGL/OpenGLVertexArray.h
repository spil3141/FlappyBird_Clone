#pragma once

#include "Tiny/Renderer/VertexArray.h"

#include <vector>
#include "glad/glad.h"

namespace Tiny {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& Quad_VertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& Quad_IndexBuffer) override;


		inline std::vector<Ref<VertexBuffer>>& GetVertexBuffers() override { return m_VertexBuffers; };
		inline Ref<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; };

	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

	};
}

