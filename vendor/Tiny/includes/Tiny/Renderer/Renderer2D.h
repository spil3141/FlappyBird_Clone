#pragma once
#include "Tiny/Core/Core.h"

//Graphics Buffer
#include "Tiny/Renderer/Buffer.h"
#include "Tiny/Renderer/VertexArray.h"

//Shader 
#include "Tiny/Renderer/Shader.h"

//Camera
#include "Tiny/Renderer/Camera/OrthoCamera.h"

#include "Tiny/Core/Core.h"
#include "Tiny/Renderer/Texture.h"

// math
#include "glm/glm.hpp"

namespace Tiny {

	struct Renderer2DData 
	{
		//Shader
		Ref<Shader> S_Shaders;

		//Buffers (VAO, VBO & IBO)
		Ref<VertexArray> Q_VertexArray;

		//Texture 

		//Camera Data
		glm::mat4 U_PVMatrix;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void SceneBegin(OrthoCamera& cam);
		static void SceneEnd();


		static void DrawQuad(const glm::vec2& position, const float Rotation_Z_Radian, const glm::vec2& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const float Rotation_Z_Radian, const glm::vec3& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const float Rotation_Z_Radian, const glm::vec2& scale, Ref<Texture2D> texture);
		static void DrawQuad(const glm::vec3& position, const float Rotation_Z_Radian, const glm::vec3& scale, Ref<Texture2D> texture);
		
	};
}

