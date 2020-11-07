#include "Scene.h"

//Third-Party Libraries
#include "ImGui/imgui.h"
#include "Random.h"

std::shared_ptr<Scene> Scene::Create()
{
	return std::make_shared<Scene>();
}

Scene::Scene()
	: m_Bg_Texture(Tiny::Texture2D::Create("res/textures/Background.png"))
{
	GameObjects.clear();

	//Defining Scene Game objects
	// Border 
	GameObject* temp1 = new GameObject("BorderTop", "res/textures/BorderTile_White.png");
	temp1->m_Position = glm::vec3(113.8f, 28.0f - 10,0.0f);
	temp1->m_Scale = glm::vec3(271.7f, 13.7f,0.0f);
	GameObjects.push_back(temp1);

	GameObject* temp2 = new GameObject("BorderButtom", "res/textures/BorderTile_White.png");
	temp2->m_Position = glm::vec3(113.8f, -28.0f + 10,0.0f);
	temp2->m_Scale = glm::vec3(271.7f, 13.7f, 0.0f);
	GameObjects.push_back(temp2);

	int number_of_platforms = 12;
	for (int i = 0; i < number_of_platforms; i++)
	{
		int random_value = Random::NextFloat() * 4.0f;
		float final_value = 0.0f;
		switch (random_value)
		{
		case 0:
		{
			final_value = 14.0f;
			break;
		}
		case 1:
		{
			final_value = 15.0f;
			break;
		}
		case 2:
		{
			final_value = 17.0f;
			break;
		}
		case 3:
		{
			final_value = 18.0f;
			break;
		}
		default:
			final_value = (float)random_value;
			break;
		}
 		//Bottom
		GameObject* temp1 = new GameObject("Platform_" + std::to_string(i) + "_a", "res/textures/platforms_template_2.png");
		temp1->m_Position = glm::vec3(10.2f + (i * 20.0f), std::clamp(-final_value,-18.0f,-14.0f),-0.2f);
		temp1->m_Scale = glm::vec3(19.7f, 30.8f,0.0f);
		//TOP
		GameObject* temp2 = new GameObject("Platform_" + std::to_string(i) + "_b", "res/textures/platforms_template_2.png");
		temp2->m_Position = glm::vec3(10.2f + (i * 20.0f), std::clamp(final_value, 14.0f, 18.0f),-0.1f);
		temp2->m_Scale = glm::vec3(19.7f, 30.8f,0.0f);
		temp2->m_Rotation = 180.0f; //뒤집다

		GameObjects.push_back(temp1);
		GameObjects.push_back(temp2);
	}


}

Scene::~Scene()
{
	for each(auto* gameobject in GameObjects)
	{
		delete gameobject;
	}
}

void Scene::Tick(float Deltatime)
{
}

void Scene::OnBegin()
{
	// Setting Scene Border Properties
	//for each (auto* gameobject in GameObjects)
	//{
	//	if (gameobject->m_Name.compare("Platform_0_a") == 0)
	//	{
	//		gameobject->m_Position = glm::vec2(46.2f, -14.9f);
	//		gameobject->m_Scale = glm::vec2(19.7f, 30.8f);
	//	}
	//	if (gameobject->m_Name.compare("Platform_0_b") == 0)
	//	{
	//		gameobject->m_Position = glm::vec2(47.2f, 14.9f);
	//		gameobject->m_Scale = glm::vec2(19.7f, 30.8f);
	//		gameobject->m_Rotation = 180.0f; //뒤집다
	//	}
	//}
}

void Scene::OnRender()
{
	//Background Quad Properties
	Tiny::Renderer2D::DrawQuad(glm::vec3(113.0f, 0.0f,-1.0f), 0.0f, glm::vec3(271.0f, 50.0f, 1.0f), m_Bg_Texture);

	for each (auto * gameobject in GameObjects)
	{
		if (gameobject->m_Name.compare("Platform_0_a") || gameobject->m_Name.compare("Platform_0_b")) 
		{
			Tiny::Renderer2D::DrawQuad(gameobject->m_Position + Pos_Offset, glm::radians(gameobject->m_Rotation), gameobject->m_Scale + Scale_Offset, gameobject->m_Texture);
			continue;
		}
		Tiny::Renderer2D::DrawQuad(gameobject->m_Position, glm::radians(gameobject->m_Rotation), gameobject->m_Scale, gameobject->m_Texture);
	}
}

void Scene::OnImGuiRender()
{
	//ImGui::Begin("Platform");
	////Translation
	//float pos_temp[] = { Pos_Offset.x,Pos_Offset.y,Pos_Offset.z };
	//ImGui::DragFloat3("Offset:", pos_temp, 0.1f);
	//Pos_Offset.x = pos_temp[0];
	//Pos_Offset.y = pos_temp[1];
	//Pos_Offset.z = pos_temp[2];
	//float pos_temp2[] = { Scale_Offset.x,Scale_Offset.y,Pos_Offset.z };
	//ImGui::DragFloat2("Scale:", pos_temp2, 0.1f);
	//Scale_Offset.x = pos_temp2[0];
	//Scale_Offset.y = pos_temp2[1];
	//Scale_Offset.z = pos_temp2[2];
	//ImGui::End();

}


