#pragma once
#include <Tiny.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string.h>

namespace GameScope {

	using namespace Tiny;
	class BirdController : public ScriptableEntity
	{
	public:
		uint32_t Score = 0;
		glm::vec2 m_Velocity = glm::vec2(0.0f, 0.0f);
	protected:
		void OnCreate() override
		{
			t_BirdTexture = Texture2D::Create("res/textures/BirdTexture.png");
			auto& spriteComp = GetComponent<SpriteRendererComponent>();
			spriteComp.Texture = t_BirdTexture;

			m_InitalScore = (uint32_t)GetComponent<TransformComponent>().position.x;
		}

		void OnDestroy() override
		{
		}

		void OnUpdate(Timestep ts) override
		{
			auto& transform = GetComponent<TransformComponent>();

			Score = (uint32_t)transform.position.x - m_InitalScore;
			m_Velocity.x = m_movementSpeed;

			if (Tiny::Input::IsKeyPressed(T_KEY_SPACE))
			{
				m_Velocity.y += m_JumpForce;
			}
			else
				m_Velocity.y -= m_Gravity;

			m_Velocity.y = std::clamp(m_Velocity.y, -20.0f, 20.1f);
			transform.position += glm::vec3(m_Velocity,0.0f) * ts.GetSeconds();
			transform.rotation = glm::vec3(0.0f, 0.0f, glm::radians((-90.0f + m_Velocity.y) * 3.6f));
		}

	private:
		Ref<Texture2D> t_BirdTexture;
		float m_Gravity = 0.4f;
		float m_JumpForce = 0.5f;
		float m_movementSpeed = 5.0f;

		uint32_t m_InitalScore;
	};
}