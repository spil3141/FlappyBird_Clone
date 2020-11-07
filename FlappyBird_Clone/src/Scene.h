#pragma once

#include "Tiny.h"

#include <iostream>
#include <vector>

#include "GameObject.h"

class Scene
{
public: 
	Scene();
	~Scene();

	void Tick(float Deltatime);
	void OnBegin();
	void OnRender();
	void OnImGuiRender();

	inline std::vector<GameObject*>& GetObjectsInWorld() { return GameObjects;  }

	static std::shared_ptr<Scene> Create();

private:
	std::vector<GameObject*> GameObjects;
	//Scene Background 
	Tiny::Ref<Tiny::Texture2D> m_Bg_Texture;


	
	//Debugging level 
	glm::vec3 Pos_Offset = { 0.0f,0.0f,0.0f };
	glm::vec3 Scale_Offset = { 1.0f,1.0f,0.0f };
	float distance_apart = 0.0f;

};


