#pragma once
#include "Tiny.h"
#include <iostream>
#include <memory.h>

#include "glm/glm.hpp"

class Bird
{
public:
	Bird();
	~Bird();

	void OnBegin();
	void Tick(float Deltatime);

	void OnRender();
	void OnImGuiRender();

	inline glm::vec3& GetPosition() { return Position;  }
	inline void SetPostion(const glm::vec3& new_pos) { Position = new_pos; }
	inline glm::vec3& GetScale() { return Scale; }


	inline glm::vec2 GetVelocity() { return Velocity; }
	inline void SetVelocity(const glm::vec2& new_vel) { Velocity = new_vel; }



	static std::shared_ptr<Bird> Create();

	//TEMP
public:
	inline void SetPause(bool value) { m_Pause = value; }
public:
	bool m_Pause = true;

private:
	//Transform
	glm::vec3 Position = glm::vec3(0.0f, 0.0f,0.1f);
	float Rotation = -90.0f;
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f,1.0f);

	//Texture 
	Tiny::Ref<Tiny::Texture2D> m_BirdTexture;


	//Physics and ImGui
	float m_Gravity = 0.4f;
	float m_JumpForce = 0.5f;
	float m_movementSpeed = 5.0f;

	//Physics
	glm::vec2 Velocity = glm::vec2(0.0f,0.0f);
	
	//Debug
	//float dt = 0.0f;
};

