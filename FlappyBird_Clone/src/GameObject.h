#pragma once

struct GameObject
{
	GameObject(std::string name, std::string texture_path)
		: m_Name(name), m_Texture(Tiny::Texture2D::Create(texture_path))
	{

	};
	~GameObject()
	{
	};

	glm::vec3 GetPosition() const { return m_Position; };
	glm::vec3 GetScale() const { return m_Scale; };
	float GetRotation() const { return m_Rotation;  }


	std::string m_Name;

	//Transform
	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	float m_Rotation = 0.0f;

	//Texture 
	Tiny::Ref<Tiny::Texture2D> m_Texture;
};