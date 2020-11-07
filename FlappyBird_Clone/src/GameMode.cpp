#include "GameMode.h"

//Third-Party Libraries
#include "ImGui/imgui.h"
#include "glm/glm.hpp"

GameMode::GameMode()
	: Scene(Scene::Create()), Player(Bird::Create()), Main_Cam((float)1280 / 720)//, DisplayOffset{ 0.0f,0.0f }
{
}

GameMode::~GameMode()
{

}

void GameMode::OnAttach()
{
	//Initializing the RandonEngine
	Random::Init();

	Player->OnBegin();
	Scene->OnBegin();

	Main_Cam.SetZoom(7.8f);
	Main_Cam.Recalibrate();

	//Font Setup 
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("res/Fonts/OpenSans-Regular.ttf", 120.0f);
}

void GameMode::OnDetach()
{
}

void GameMode::OnUpdate(Tiny::Timestep dt)
{

	Scene->Tick(dt.GetSeconds());
	Player->Tick(dt.GetSeconds());
	Main_Cam.OnUpdate(dt);

	//Camera Follow Player
	FollowPlayer(Main_Cam.GetCamera(), Player);

	//Render Scene
	Tiny::RenderCommand::SetClearColor({ 0.0f,0.0f,0.0f,1.0f });
	Tiny::RenderCommand::Clear();
	Tiny::Renderer2D::SceneBegin(Main_Cam.GetCamera());
	Scene->OnRender();
	Player->OnRender();
	Tiny::Renderer2D::SceneEnd();

	//Collision Detection 

	if (CheckCollisionWithScene(Player))
	{
		ResetLevel();
	}

	// GameState and Input Manager
	if (Tiny::Input::IsKeyPressed(T_KEY_ENTER))
	{
		Player->SetPause(false);
		m_GameState = GameState::Playing;
	}
}

void GameMode::OnEvent(Tiny::Event& e)
{
	Main_Cam.OnEvent(e);

	Tiny::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Tiny::KeyPressedEvent>(T_BIND_EVENT_FN(&GameMode::OnKeyPressed));

}

void GameMode::ResetLevel()
{
	m_GameState = GameState::Paused;
	Player->m_Pause = true;
	Player->SetPostion(glm::vec3(0.0f,0.0f,Player->GetPosition().z));
}

void GameMode::FollowPlayer(Tiny::OrthoCamera& Cam, Tiny::Ref<Bird> player)
{
	Cam.SetPostion(player->GetPosition());
}

bool GameMode::CheckCollisionWithScene(Tiny::Ref<Bird>& player)
{
	//A typical Quad Vertices
	glm::vec4 QuadVertices[] = {
		{-0.5,-0.5,0.0f,1.0f},
		{ 0.5,-0.5,0.0f,1.0f},
		{ 0.5, 0.5,0.0f,1.0f},
		{-0.5, 0.5,0.0f,1.0f},	
	};

	//The Bird Quad Vertices
	glm::vec4 playerQuadTransVerticePos[4];

	for (int i =0; i < 4; i++)
	{
		glm::mat4 T = glm::translate(glm::mat4(1.0f),Player->GetPosition());
		glm::mat4 R = glm::rotate(glm::mat4(1.0f),glm::radians(0.0f),glm::vec3(0.0f,0.0f,1.0f));
		glm::mat4 S = glm::scale(glm::mat4(1.0f),Player->GetScale());
		playerQuadTransVerticePos[i] =  T * R * S * QuadVertices[i];
		//T_INFO("{0} : ({1},{2},{3},{4})", i, playerQuadTransVerticePos[i].x, playerQuadTransVerticePos[i].y, playerQuadTransVerticePos[i].z, playerQuadTransVerticePos[i].w);
	}

	//The Scene Quad Vertices
	glm::vec4 PillarTriangleVertices[] = {
		{-0.5 * 0.9,-0.5 * 0.9,0.0f,1.0f},
		{ 0.5 * 0.9,-0.5 * 0.9,0.0f,1.0f},
		{ 0.0, 0.5 * 0.84,0.0f,1.0f}
	};
	
	auto& gameobjects = Scene->GetObjectsInWorld();
	//transverse all gameobject to find border

	
	for (int j = 0; j < (int)gameobjects.size(); j++)
	{
		glm::vec4 QuadTransVerticePos[4];

		//Borders
		if (gameobjects[j]->m_Name.compare("BorderTop") == 0 || gameobjects[j]->m_Name.compare("BorderButtom") == 0)
		{

			for (int i = 0; i < 4; i++)
			{
				glm::mat4 T = glm::translate(glm::mat4(1.0f), gameobjects[j]->GetPosition());
				glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(gameobjects[j]->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
				glm::mat4 S = glm::scale(glm::mat4(1.0f), gameobjects[j]->GetScale());
				QuadTransVerticePos[i] = T * R * S * QuadVertices[i];
			}

			for (auto& p : playerQuadTransVerticePos)
			{
				if (PointInTri({ p.x,p.y },
					glm::vec2(QuadTransVerticePos[0].x, QuadTransVerticePos[0].y),
					glm::vec2(QuadTransVerticePos[1].x, QuadTransVerticePos[1].y),
					glm::vec2(QuadTransVerticePos[2].x, QuadTransVerticePos[2].y)) || 
					PointInTri({ p.x,p.y },
						glm::vec2(QuadTransVerticePos[2].x, QuadTransVerticePos[2].y),
						glm::vec2(QuadTransVerticePos[3].x, QuadTransVerticePos[3].y),
						glm::vec2(QuadTransVerticePos[0].x, QuadTransVerticePos[0].y))
					)
				{
					return true;
				}
			}
		}
		// Pillars
		if (gameobjects[j]->m_Name.length() > 9)
		{
			if (gameobjects[j]->m_Name.c_str()[0] == 'P' &&
				gameobjects[j]->m_Name.c_str()[1] == 'l' && 
				gameobjects[j]->m_Name.c_str()[2] == 'a' &&
				gameobjects[j]->m_Name.c_str()[3] == 't' &&
				gameobjects[j]->m_Name.c_str()[4] == 'f' &&
				gameobjects[j]->m_Name.c_str()[5] == 'o' &&
				gameobjects[j]->m_Name.c_str()[6] == 'r' &&
				gameobjects[j]->m_Name.c_str()[7] == 'm' &&
				gameobjects[j]->m_Name.c_str()[8] == '_'
				)
			{

				for (int i = 0; i < 4; i++)
				{
					glm::mat4 T = glm::translate(glm::mat4(1.0f), gameobjects[j]->GetPosition());
					glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(gameobjects[j]->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
					glm::mat4 S = glm::scale(glm::mat4(1.0f), gameobjects[j]->GetScale());
					QuadTransVerticePos[i] = T * R * S * PillarTriangleVertices[i];
				}

				for (auto& p : playerQuadTransVerticePos)
				{
					if (PointInTri({ p.x,p.y },
						glm::vec2(QuadTransVerticePos[0].x, QuadTransVerticePos[0].y),
						glm::vec2(QuadTransVerticePos[1].x, QuadTransVerticePos[1].y),
						glm::vec2(QuadTransVerticePos[2].x, QuadTransVerticePos[2].y))
						)
					{
						return true;
					}
				}
			}

		}
	}
	

	//for (int i = 0; i < 4; i++)
	//{
	//	auto& gameobjects = Scene->GetObjectsInWorld();
	//	//transverse all gameobject to find border
	//	for (int j = 0; j < (int)gameobjects.size(); j++)
	//	{
	//		if (gameobjects[j]->m_Name.compare("BorderTop") == 0)
	//		{
	//			glm::mat4 T = glm::translate(glm::mat4(1.0f), gameobjects[j]->GetPosition());
	//			glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(gameobjects[j]->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
	//			glm::mat4 S = glm::scale(glm::mat4(1.0f), gameobjects[j]->GetScale());
	//			topborderQuadTransVerticePos[i] = T * R * S * QuadVertices[i];
	//		}else if (gameobjects[j]->m_Name.compare("BorderButtom") == 0)
	//		{
	//			glm::mat4 T = glm::translate(glm::mat4(1.0f), gameobjects[j]->GetPosition());
	//			glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(gameobjects[j]->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
	//			glm::mat4 S = glm::scale(glm::mat4(1.0f), gameobjects[j]->GetScale());
	//			buttomborderQuadTransVerticePos[i] = T * R * S * QuadVertices[i];
	//		}else if (gameobjects[j]->m_Name.compare("Platform_") == 0)
	//		{
	//			glm::mat4 T = glm::translate(glm::mat4(1.0f), gameobjects[j]->GetPosition());
	//			glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(gameobjects[j]->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
	//			glm::mat4 S = glm::scale(glm::mat4(1.0f), gameobjects[j]->GetScale());
	//			buttomborderQuadTransVerticePos[i] = T * R * S * QuadVertices[i];
	//		}
	//	}
	//}


	/*for (auto& p : playerQuadTransVerticePos)
	{
		if (PointInTri({ p.x,p.y },
			glm::vec2(topborderQuadTransVerticePos[0].x,topborderQuadTransVerticePos[0].y),
			glm::vec2(topborderQuadTransVerticePos[1].x,topborderQuadTransVerticePos[1].y),
			glm::vec2(topborderQuadTransVerticePos[0].x,topborderQuadTransVerticePos[0].y)) ||
			PointInTri({ p.x,p.y },
				glm::vec2(topborderQuadTransVerticePos[2].x, topborderQuadTransVerticePos[2].y),
				glm::vec2(topborderQuadTransVerticePos[3].x, topborderQuadTransVerticePos[3].y),
				glm::vec2(topborderQuadTransVerticePos[0].x, topborderQuadTransVerticePos[0].y)))
		{
			return true;
		}
		if (PointInTri({ p.x,p.y },
			glm::vec2(buttomborderQuadTransVerticePos[0].x, buttomborderQuadTransVerticePos[0].y),
			glm::vec2(buttomborderQuadTransVerticePos[1].x, buttomborderQuadTransVerticePos[1].y),
			glm::vec2(buttomborderQuadTransVerticePos[0].x, buttomborderQuadTransVerticePos[0].y)) ||
			PointInTri({ p.x,p.y },
				glm::vec2(buttomborderQuadTransVerticePos[2].x, buttomborderQuadTransVerticePos[2].y),
				glm::vec2(buttomborderQuadTransVerticePos[3].x, buttomborderQuadTransVerticePos[3].y),
				glm::vec2(buttomborderQuadTransVerticePos[0].x, buttomborderQuadTransVerticePos[0].y)))
		{
			return true;
		}
	}*/

	/*T_INFO("Bird");
	T_INFO("	POS : ({0}, {1}, {2}, {3})", playerQuadTransVerticePos[0].x, playerQuadTransVerticePos[0].y, playerQuadTransVerticePos[0].z, playerQuadTransVerticePos[0].w);
	T_INFO("	POS : ({0}, {1}, {2}, {3})", playerQuadTransVerticePos[1].x, playerQuadTransVerticePos[1].y, playerQuadTransVerticePos[1].z, playerQuadTransVerticePos[1].w);
	T_INFO("	POS : ({0}, {1}, {2}, {3})", playerQuadTransVerticePos[2].x, playerQuadTransVerticePos[2].y, playerQuadTransVerticePos[2].z, playerQuadTransVerticePos[2].w);
	T_INFO("	POS : ({0}, {1}, {2}, {3})", playerQuadTransVerticePos[3].x, playerQuadTransVerticePos[3].y, playerQuadTransVerticePos[3].z, playerQuadTransVerticePos[3].w);

	T_INFO("BorderTOP");
	T_INFO("	POS : ({0}, {1}, {2}, {3})", topborderQuadTransVerticePos[0].x, topborderQuadTransVerticePos[0].y, topborderQuadTransVerticePos[0].z, topborderQuadTransVerticePos[0].w);
	T_INFO("	POS : ({0}, {1}, {2}, {3})", topborderQuadTransVerticePos[1].x, topborderQuadTransVerticePos[1].y, topborderQuadTransVerticePos[1].z, topborderQuadTransVerticePos[1].w);
	T_INFO("	POS : ({0}, {1}, {2}, {3})", topborderQuadTransVerticePos[2].x, topborderQuadTransVerticePos[2].y, topborderQuadTransVerticePos[2].z, topborderQuadTransVerticePos[2].w);
	T_INFO("	POS : ({0}, {1}, {2}, {3})", topborderQuadTransVerticePos[3].x, topborderQuadTransVerticePos[3].y, topborderQuadTransVerticePos[3].z, topborderQuadTransVerticePos[3].w);*/

	return false;
}

bool GameMode::PointInTri(const glm::vec2& P, glm::vec2& A, glm::vec2& B, glm::vec2& C)
{
	//Method 1
	double s1 = C.y - A.y;
	double s2 = C.x - A.x;
	double s3 = B.y - A.y;
	double s4 = P.y - A.y;

	double w1 = (A.x * s1 + s4 * s2 - P.x * s1) / (s3 * s2 - (B.x - A.x) * s1);
	double w2 = (s4 - w1 * s3) / s1;

	return w1 >= 0.0 && w2 >= 0.0 && (w1 + w2) <= 1.0;

	////Method 2
	//float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	//float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	//if ((s < 0) != (t < 0))
	//	return false;

	//float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	//return A < 0 ?
	//	(s <= 0 && s + t >= A) :
	//	(s >= 0 && s + t <= A);
}

void GameMode::OnImGuiRender()
{
	Player->OnImGuiRender();
	Scene->OnImGuiRender();

	// Score Display
	switch (m_GameState)
	{
	case GameState::Playing:
	{
		auto pos = ImGui::GetWindowPos();
		std::string display = "Score: " + std::to_string(GetPlayerScore());
		ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0, pos, 0xffffffff, display.c_str());
		break;
	}
	case GameState::Paused:
	{
		auto pos_1 = ImGui::GetWindowPos();
		auto pos_2 = pos_1;
		auto width = Tiny::Application::Get().GetWindow().GetWidth();
		auto height = Tiny::Application::Get().GetWindow().GetHeight();
		pos_1.x += width * 0.5f - 494.0f;
		pos_2.x += width * 0.5f - 494.0f;
		pos_1.y += 50.0;
		pos_2.y += 200.0;
		ImGui::GetForegroundDrawList()->AddText(m_Font,120.0f, pos_1, 0xffffffff, "Press Enter to Play");

		ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0f, pos_2, 0xffffffff, "Use space for vertical propulsion");
		break;
	}
	}

	/*bool show = false;
	ImGui::ShowDemoWindow(&show);*/

	//ImGui::Begin("Performance Check");
	//{
	//	ImGui::Checkbox("ShowDemo", &showDemo);
	//	//ImGui::DragFloat2("Score Pos: ", DisplayOffset,0.2f);

	//	float framerate = ImGui::GetIO().Framerate;\
	//	float frametime = framerate / 60.0f;
	//	//frametimes[offsetvalue] = frametime;
	//	//offsetvalue = (offsetvalue + 1) % IM_ARRAYSIZE(frametimes);
	//	//const char* outlay = "Frametime (ms)";
	//	//ImGui::PlotLines("", frametimes, IM_ARRAYSIZE(frametimes), 0, outlay, 0.0f, 10.0f, ImVec2(0, 80.0f));
	//	//ImGui::Text("Frametime (sec): %f", frametime);
	//	ImGui::Text("Framerate: %f", framerate);
	//}
	//ImGui::End();

}

bool GameMode::OnKeyPressed(Tiny::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == T_KEY_R)
	{
		ResetLevel();
	}
	return false;
}
