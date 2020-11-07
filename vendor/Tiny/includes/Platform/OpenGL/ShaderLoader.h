#pragma once

#include <string.h>

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

	class ShaderLoader
	{
	public:
		ShaderLoader();
		~ShaderLoader();
		unsigned int createShaderProgram(const char* ShaderFilePath);
	private:
		unsigned int CompileShader(unsigned int type, std::string& source);
		ShaderProgramSource parseShader(const char* filePath);
	};

}