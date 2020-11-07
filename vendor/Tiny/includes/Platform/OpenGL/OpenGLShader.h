#pragma once

#include <string.h>
#include "Tiny/Renderer/Shader.h"

namespace Tiny {
	
	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	enum ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string path);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetMat4(const std::string& uniformName, const glm::mat4& data) const override;
		
		void SetVec4(const std::string& uniformName, const glm::vec4& data) const override;
		
		virtual void SetInt(const std::string& uniformName, const int data) const override;



	private:
		unsigned int createShaderProgram(const char* ShaderFilePath);
		unsigned int CompileShader(unsigned int type, std::string& source);
		ShaderProgramSource parseShader(const char* filePath);
	private:
		unsigned int m_ProgramID;
		const std::string m_Path;
	};

	
}

