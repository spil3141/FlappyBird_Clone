#pragma once

#include "Tiny/Renderer/Shader.h"
#include "Tiny/Renderer/Camera/Camera.h"


//OpenGL Mathematics Library
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective


//TEMP
//#include "Mesh.h"
#include "Tiny/Renderer/Objects/Actor.h"

namespace Tiny {

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Clear(); //should be move to a static RenderCommand class


		static void SceneBegin(Camera& Camera);
		static void EndScene();
		static void Submit(Ref<Shader> shader, Actor& actor);



	private:
		struct SceneData {
			glm::mat4 ProjectionViewMatrix;
		};

		static Scope<SceneData> m_SceneData;
	};

}







/*static void Init(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
static void Init(unsigned int& vao, unsigned int& vbo, std::vector<Vertex> vertices);*/
/*static void Draw(unsigned int ShaderProgram, unsigned int& vao, unsigned int& ebo, unsigned int count);
static void Draw(unsigned int ShaderProgram, unsigned int& vao, unsigned int& ebo, unsigned int count, glm::vec3 pos);
static void Draw(unsigned int ShaderProgram, unsigned int& vao, unsigned int count, glm::vec3 pos);
static void DrawRotatingPrimitiveZ(Ref<Shader>& shader, unsigned int& vao, unsigned int count, glm::vec3 pos,float rotation);*/
/*static void DrawPrimitiveCamera(Ref<Shader>& shader, Actor& actor, unsigned int count, glm::vec3 pos, Camera& PerspCamera);*/