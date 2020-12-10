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

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const OrthoCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Stats
		struct Statistics
		{
			float FrameRenderTime; // collect render time for multiple frames
			float CurrentFrameBeginTime = 0.0f;
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; }

		};
		static void ResetStats();
		static Statistics GetStats();
		static void StatsBeginFrame();
		static void StatsEndFrame();

	private:
		static void StartBatch();
		static void NextBatch();
	};

	//struct Renderer2DData 
	//{
	//	//Shader
	//	Ref<Shader> S_Shaders;

	//	//Buffers (VAO, VBO & IBO)
	//	Ref<VertexArray> Q_VertexArray;

	//	//Texture 

	//	//Camera Data
	//	glm::mat4 U_PVMatrix;
	//};

	//class Renderer2D
	//{
	//public:
	//	static void Init();
	//	static void Shutdown();

	//	static void SceneBegin(OrthoCamera& cam);
	//	static void SceneEnd();


	//	static void DrawQuad(const glm::vec2& position, const float Rotation_Z, const glm::vec2& scale, const glm::vec4& color);
	//	static void DrawQuad(const glm::vec3& position, const float Rotation_Z, const glm::vec3& scale, const glm::vec4& color);
	//	static void DrawQuad(const glm::vec2& position, const float Rotation_Z, const glm::vec2& scale, Ref<Texture2D> texture);
	//	static void DrawQuad(const glm::vec3& position, const float Rotation_Z, const glm::vec3& scale, Ref<Texture2D> texture);
	//	
	//};
}

