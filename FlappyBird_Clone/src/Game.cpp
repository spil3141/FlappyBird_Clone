#include "Game.h"

#include <array>
#include <ImGui/imgui.h>

// Scripts
#include "Scripts/BirdController.h"
#include "Utils/Math.h"

namespace GameScope {

	Game::Game()
		: Layer("Game Layer")
	{
		//Tiny::Application::Get().GetWindow().SetVSync(false);
		t_PillarsTexture = Texture2D::Create("res/textures/Triangle.png");


		//Font Setup 
		ImGuiIO io = ImGui::GetIO();
		m_Font = io.Fonts->AddFontFromFileTTF("res/Fonts/OpenSans-Regular.ttf", 120.0f);
	}

	Game::~Game()
	{

	}

	void Game::OnAttach()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_MenuScene = CreateRef<Scene>();

		Application& app = Application::Get();
		/**********************
			Menu Scene
		***********************/
		// Menu Camera
		e_MenuCamera = m_MenuScene->CreateEntity("Menu Camera");
		auto& mce = e_MenuCamera.AddComponent<CameraComponent>();
		mce.Camera.SetViewportSize(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		auto& menucamtranform = e_MenuCamera.GetComponent<TransformComponent>();
		menucamtranform.position = glm::vec3(0.0f, 0.0f, 0.5f);

		e_Title = m_MenuScene->CreateEntity("Game Title");
		auto& title_sprite = e_Title.AddComponent<SpriteRendererComponent>();
		title_sprite.Texture = Texture2D::Create("res/textures/TitleTexture.png");
		auto& title_transform = e_Title.GetComponent<TransformComponent>();
		title_transform.scale = glm::vec3(10.7f, 2.6f, 0.0f);
		title_transform.position = glm::vec3(0.0f, 0.0f, 0.3f);

		e_MenuBG = m_MenuScene->CreateEntity("Menu Background");
		e_MenuBG.AddComponent<SpriteRendererComponent>(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
		auto& menubgtrans = e_MenuBG.GetComponent<TransformComponent>();
		menubgtrans.scale = glm::vec3(50.0f, 50.0f, 0.0f);
		menubgtrans.position = glm::vec3(0.0f, 0.0f, -0.2f);

		/**********************
			Main Scene 
		***********************/
		// Game Camera
		e_Camera = m_ActiveScene->CreateEntity("Game Camera");
		auto& ce = e_Camera.AddComponent<CameraComponent>();
		ce.Camera.SetViewportSize(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		auto& camtranform = e_Camera.GetComponent<TransformComponent>();
		camtranform.position = glm::vec3(0.0f, 0.0f, 0.5f);


		// Bird Entity Creation
		e_Player = GetScene()->CreateEntity("Player");
		e_Player.AddComponent<SpriteRendererComponent>();
		e_Player.AddComponent<NativeScriptComponent>().Bind<BirdController>();


		// Create Pillars
		int number_of_platforms = 20;
		float lerp_z = -0.2f;
		for (int i = 0; i < number_of_platforms; i++)
		{
			lerp_z = Mathf::lerp(lerp_z, 0.3f, 0.1f);
			//TOP
			Entity PillarTop = m_ActiveScene->CreateEntity("PillarTop");
			PillarTop.AddComponent<SpriteRendererComponent>(t_PillarsTexture);
			auto& pt_trans = PillarTop.GetComponent<TransformComponent>();
			pt_trans.position = glm::vec3(10.2f + (i * 20.0f), 8.0f, lerp_z);
			pt_trans.scale = glm::vec3(15.0f, 15.0f, 0.0f);
			pt_trans.rotation = glm::vec3(0.0f, 0.0f, 3.14f);

			//Bottom
			Entity PillarButtom = m_ActiveScene->CreateEntity("PillarButton");
			PillarButtom.AddComponent<SpriteRendererComponent>(t_PillarsTexture);
			auto& pb_trans = PillarButtom.GetComponent<TransformComponent>();
			pb_trans.position = glm::vec3(10.2f + (i * 20.0f), -8.0f, lerp_z);
			pb_trans.scale = glm::vec3(15.0f, 15.0f, 0.0f);
			pb_trans.rotation.z = 0.0f; //µÚÁý´Ù

			e_Pillars.push_back(PillarButtom);
			e_Pillars.push_back(PillarTop);
		}


		// Ceiling, background and Floor 
		e_Floor = m_ActiveScene->CreateEntity("Floor");
		e_Floor.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		e_Ceiling = m_ActiveScene->CreateEntity("Ceiling");
		e_Ceiling.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		e_BG = m_ActiveScene->CreateEntity("Background");
		e_BG.AddComponent<SpriteRendererComponent>(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		auto& bgt = e_BG.GetComponent<TransformComponent>();
		bgt.scale = glm::vec3(50.0f, 50.0f, 0.0f);
	}

	void Game::OnDetach()
	{

	}

	void Game::OnUpdate(Timestep dt)
	{	
		// Update Scenes

		RenderCommand::SetClearColor({ 0.0f,0.0f,0.0f,1.0f });
		RenderCommand::Clear();
		if (m_GameState == GameState::PLAYING /*&& m_GameState == GameState::PAUSED*/)
		{
			// TEMP: Replace when entities can reference each other. 
			//   Background, Floor and Ceiling 
			auto& pt = e_Player.GetComponent<TransformComponent>();
			auto& bgt = e_BG.GetComponent<TransformComponent>();
			bgt.position = glm::vec3(pt.position.x, 0.0f, -0.2f);
			auto& ft = e_Floor.GetComponent<TransformComponent>();
			ft.position = glm::vec3(pt.position.x, 28.0f, -0.1f);
			ft.scale = glm::vec3(40.0f, 40.0f, 0.0f);
			auto& ct = e_Ceiling.GetComponent<TransformComponent>();
			ct.position = glm::vec3(pt.position.x, -28.0f, -0.1f);
			ct.scale = glm::vec3(40.0f, 40.0f, 0.0f);

			m_ActiveScene->OnUpdate(dt);

			// Collision check with Ceiling and Floor
			if (CheckEntityCollision2D(e_Player, e_Ceiling) || CheckEntityCollision2D(e_Player, e_Floor))
			{
				m_GameState = GameState::GAMEOVER;
				ResetGame();
			}
			// BAD SOLUTION (expensive)-> Collision check with pillars
			for (auto& entity : e_Pillars)
			{
				if (CheckEntityNTriCollision2D(e_Player, entity))
				{
					m_GameState = GameState::GAMEOVER;
					ResetGame();
				}
			}

			CamFollowPlayer();
		}
		else if (m_GameState == GameState::GAMEOVER)
		{
			m_MenuScene->OnUpdate(dt);
		}


		
	}

	void Game::CamFollowPlayer()
	{
		auto& camtransform = e_Camera.GetComponent<TransformComponent>();
		auto& playertransform = e_Player.GetComponent<TransformComponent>();
		camtransform.position = playertransform.position;
	}

	bool Game::CheckEntityCollision2D(Entity& entity1, Entity& entity2)
	{
		std::array<glm::vec4,4> entity1_quad_vertices;
		std::array<glm::vec4,4> entity2_quad_vertices;

		auto& transform1 = entity1.GetComponent<TransformComponent>();
		auto& transform2 = entity2.GetComponent<TransformComponent>();

		for (int i = 0; i < 4; i++)
		{
			entity1_quad_vertices[i] = transform1.GetTransform() * s_QuadVertices[i];
			entity2_quad_vertices[i] = transform2.GetTransform() * s_QuadVertices[i];
		}

		for (auto& p : entity1_quad_vertices)
		{
			if (PointInTri({ p.x,p.y },
				glm::vec2(entity2_quad_vertices[0].x, entity2_quad_vertices[0].y),
				glm::vec2(entity2_quad_vertices[1].x, entity2_quad_vertices[1].y),
				glm::vec2(entity2_quad_vertices[2].x, entity2_quad_vertices[2].y)) ||
				PointInTri({ p.x,p.y },
					glm::vec2(entity2_quad_vertices[2].x, entity2_quad_vertices[2].y),
					glm::vec2(entity2_quad_vertices[3].x, entity2_quad_vertices[3].y),
					glm::vec2(entity2_quad_vertices[0].x, entity2_quad_vertices[0].y))
				)
				return true;
		}
		return false;
	}

	bool Game::CheckEntityNTriCollision2D(Entity& entity, Entity& tri_entity)
	{
		std::array<glm::vec4, 4> Entity_quad_vertices;
		std::array<glm::vec4, 4> TriangularEntity_quad_vertices;

		auto& transform1 = entity.GetComponent<TransformComponent>();
		auto& transform2 = tri_entity.GetComponent<TransformComponent>();

		for (int i = 0; i < 4; i++)
		{
			Entity_quad_vertices[i] = transform1.GetTransform() * s_QuadVertices[i];
			TriangularEntity_quad_vertices[i] = transform2.GetTransform() * s_TriangleVertices[i];
		}

		for (auto& p : Entity_quad_vertices)
		{
			if (PointInTri({ p.x,p.y },
				glm::vec2(TriangularEntity_quad_vertices[0].x, TriangularEntity_quad_vertices[0].y),
				glm::vec2(TriangularEntity_quad_vertices[1].x, TriangularEntity_quad_vertices[1].y),
				glm::vec2(TriangularEntity_quad_vertices[2].x, TriangularEntity_quad_vertices[2].y)) 
				)
				return true;
		}
		return false;
	}

	bool Game::PointInTri(const glm::vec2& P, glm::vec2& A, glm::vec2& B, glm::vec2& C)
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

	void Game::OnEvent(Event & e)
	{
		EventDispatcher dispatch(e);
		dispatch.Dispatch<WindowResizeEvent>(T_BIND_EVENT_FN(Game::OnResizeEvent));
		dispatch.Dispatch<KeyPressedEvent>(T_BIND_EVENT_FN(Game::OnKeyPressedEvent));
	}


	void Game::OnImGuiRender()
	{
#ifdef T_DEBUG
		{
			auto stats = Tiny::Renderer2D::GetStats();
			auto pos = ImGui::GetWindowPos();
			ImGui::GetForegroundDrawList()->AddText(m_Font, 23.0, ImVec2(pos.x - 300, pos.y + 32 + 30 + 30), 0xffffffff,
				("Draw Calls:" + std::to_string(stats.DrawCalls)).c_str());
			ImGui::GetForegroundDrawList()->AddText(m_Font, 23.0, ImVec2(pos.x - 300, pos.y + 32 + 30 + 30 + 30), 0xffffffff,
				("Quads: " + std::to_string(stats.QuadCount)).c_str());
			ImGui::GetForegroundDrawList()->AddText(m_Font, 23.0, ImVec2(pos.x - 300, pos.y + 32 + 30 + 30 + 30 + 30), 0xffffffff,
				("Vertices: " + std::to_string(stats.GetTotalVertexCount())).c_str());
			ImGui::GetForegroundDrawList()->AddText(m_Font, 23.0, ImVec2(pos.x - 300, pos.y + 32 + 30 + 30 + 30 + 30 + 30), 0xffffffff,
				("Indices: " + std::to_string(stats.GetTotalIndexCount())).c_str());

			// Debug: Framerate related code
			float framerate = ImGui::GetIO().Framerate;
			//float averageRenderTime = (float)(1000.0f * stats.FrameRenderTime); // nb: wont be accurate until we have gathered at least stats.FrameRenderTime().size() results
			/*if ((Time::Fixedtime() - Timer > 1.0f))
			{
				Timer += 1.0f;
				framerate = frames;
				frames = 0;
			}
			frames++;*/
			ImGui::GetForegroundDrawList()->AddText(m_Font, 23.0, ImVec2(pos.x - 300, pos.y + 32 + 30 + 30 + 30 + 30 + 30 + 30), 0xffffffff,
				("fps: " + std::to_string(framerate) + " (" + std::to_string((1/ (framerate != 0 ? framerate : 1)) * 1000.0f) + " ms)").c_str());


			//// Debug
			//ImGui::Begin("Performance Check");
			//{
			//	auto stats = Tiny::Renderer2D::GetStats();
			//	auto pos = ImGui::GetWindowPos();
			//	ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0, pos, 0xffffffff,
			//		"Renderer2D Stats:");
			//	ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0, pos, 0xffffffff,
			//		("Draw Calls: " + std::to_string(stats.DrawCalls)).c_str());

			//	//ImGui::Text("Renderer2D Stats:");
			//	//ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			//	//ImGui::Text("Quads: %d", stats.QuadCount);
			//	//ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			//	//ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
			//	//ImGui::Separator();
			//	//float framerate = ImGui::GetIO().Framerate;
			//	//float averageRenderTime = (float)(1000.0f * stats.FrameRenderTime); // nb: wont be accurate until we have gathered at least stats.FrameRenderTime().size() results
			//	//ImGui::Text("Average frame render time: %8.5f ms (%5.0f fps)", averageRenderTime, framerate);
			//}
			//ImGui::End();
		}
#endif

		{

			NativeScriptComponent& script = e_Player.GetComponent<NativeScriptComponent>();
			BirdController* birdscript = (BirdController*)script.Instance;
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();

			switch (m_GameState)
			{
			case GameState::PLAYING:
			{
				auto text_1_pos = pos;
				text_1_pos.x += -200.0f;
				std::string display = "Score: " + std::to_string(birdscript->Score);
				ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0f, text_1_pos, 0xffffffff, display.c_str());
				break;
			}
			case GameState::GAMEOVER:
			{
				auto text_2_pos = pos;
				text_2_pos.x += width * 0.5f - 494.0f;
				text_2_pos.y += height - 200.0f;
				ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0f, text_2_pos, 0xffffffff, "Use space for vertical propulsion");
				break;
			}
			}
		}

	}

	bool Game::OnResizeEvent(WindowResizeEvent & e)
	{
		m_ActiveScene->OnViewportResize(e.GetWidth(), e.GetHeight());
		m_MenuScene->OnViewportResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	bool Game::OnKeyPressedEvent(KeyPressedEvent & e)
	{
		if (e.GetKeyCode() == KeyCode::Enter && m_GameState == GameState::GAMEOVER) // Player game
		{
			m_GameState = GameState::PLAYING;
		}
		/*if (e.GetKeyCode() == T_KEY_ESCAPE)
		{
			if (m_GameState == GameState::PLAYING)
				m_GameState = GameState::PAUSED;
			else if (m_GameState == GameState::PAUSED)
				m_GameState = GameState::PLAYING;
		}*/

		return false;
	}

	void Game::ResetGame()
	{
		auto& transform = e_Player.GetComponent<TransformComponent>();
		transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
		BirdController* playerscript = (BirdController*) e_Player.GetComponent<NativeScriptComponent>().Instance;
		playerscript->m_Velocity = glm::vec3(0.0f);
	}

}
