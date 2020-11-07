#pragma once 

#include <string>
#include "Tiny/Core/Core.h"

#include "glm/glm.hpp"

namespace Tiny {

	enum class ShaderPrimitiveType {
		None = 0, Float
	};


	class Shader
	{
	public:
		virtual ~Shader() = default;

		//Creating ShaderProgram/Compiling/Binding
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		//Passing Uniforms to Shader
		virtual void SetMat4(const std::string& uniformName, const glm::mat4& data) const = 0;
		virtual void SetVec4(const std::string& uniformName, const glm::vec4& data) const = 0;
		virtual void SetInt(const std::string& uniformName, const int data) const = 0;

		static Ref<Shader> Create(const std::string path);
	};
}