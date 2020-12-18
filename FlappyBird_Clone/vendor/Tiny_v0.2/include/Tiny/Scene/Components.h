#pragma once

#include "SceneCamera.h"
#include "ScriptableEntity.h"

#include "Tiny/Renderer/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Tiny {

	struct TransformComponent
	{
		glm::vec3 position{ 0.0f,0.0f,0.0f };
		glm::vec3 rotation = { 0.0f,0.0f,0.0f };
		glm::vec3 scale = { 1.0f,1.0f,1.0f };


		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& pos)
			: position(pos){}

		glm::mat4 GetTransform() const
		{
			//glm::mat4 rotate = glm::toMat4(glm::qua(rotation));
			glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f,0.0f,0.0f }) *
				glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f,1.0f,0.0f }) *
				glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f,0.0f,1.0f });

			return glm::translate(glm::mat4(1.0f),position) * rotate * glm::scale(glm::mat4(1.0f),scale);
		}

	};

	struct TagComponent {

		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string l_tag)
			: tag(l_tag) {}

		operator std::string& () { return tag; }
		operator const std::string& () { return tag; }
		inline bool operator==(const std::string& other) { return strcmp(this->tag.c_str(), other.c_str()) == 0; }

	};

	struct SpriteRendererComponent
	{
		Ref<Texture2D> Texture;
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4 & color)
			: Color(color) {}
		SpriteRendererComponent(Ref<Texture2D> texture)
			: Texture(texture) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}

