#pragma once

#include "Tiny/Renderer/Shader.h"

namespace Tiny {


	enum class VertexArribute {
		POS = 0,
		COLOR = 1,
		UV = 2
	};


	// ------- Vertex Buffer ------------------------------------

	class VertexBuffer
	{
	public:
		~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetLayout(ShaderPrimitiveType type, VertexArribute vertexAttrib) = 0;

		static Ref<VertexBuffer> Create(const void* vertices, uint32_t size);

	};

	// ------- Index Buffer ------------------------------------

	class IndexBuffer
	{
	public:
		~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);

	};

}
