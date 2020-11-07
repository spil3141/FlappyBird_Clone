#pragma once

#include "Tiny/Renderer/Buffer.h"

namespace Tiny {

	// ------- Vertex Buffer ----------------------------------------------


	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		void Bind() override;
		void Unbind() override;


		void SetLayout(ShaderPrimitiveType type, VertexArribute) override;

	private:
		uint32_t m_Renderer_ID;
	};

	// ------- Index Buffer ----------------------------------------------

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		void Bind() override;
		void Unbind() override;


		inline uint32_t GetCount() const override { return m_IndicesCount; };

	private:
		uint32_t m_Renderer_ID;
		uint32_t m_IndicesCount;
	};
}