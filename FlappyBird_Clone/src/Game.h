#pragma once
#include <Tiny.h>

#include <vector>
#include <ImGui/imgui.h>

using namespace Tiny;
namespace GameScope {

	enum class GameState {
		PLAYING = 0,
		GAMEOVER
		//PAUSED
	};

	// Player Quad vertices
	static glm::vec4 s_QuadVertices[] = {
			{-0.5,-0.5,0.0f,1.0f},
			{ 0.5,-0.5,0.0f,1.0f},
			{ 0.5, 0.5,0.0f,1.0f},
			{-0.5, 0.5,0.0f,1.0f},
	};

	static glm::vec4 s_TriangleVertices[] = {
		{-0.5 * 0.9, -0.5 * 0.9 , 0.0f, 1.0f},
		{ 0.5 * 0.9, -0.5 * 0.9 , 0.0f, 1.0f},
		{ 0.0      ,  0.5 * 0.84, 0.0f, 1.0f}
	};

	class Game : public Layer
	{
	public:
		Game();
		~Game();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Tiny::Timestep dt) override;
		virtual void OnEvent(Tiny::Event& e) override;
		virtual void OnImGuiRender() override;

	private:
		Ref<Scene> GetScene() { return m_ActiveScene; }
		void CamFollowPlayer();
		bool CheckEntityCollision2D(Entity& entity1, Entity& entity2);
		bool CheckEntityNTriCollision2D(Entity& entity, Entity& tri_entity);
		bool PointInTri(const glm::vec2& P, glm::vec2& A, glm::vec2& B, glm::vec2& C);
		void ResetGame();
	private: // Events
		bool OnResizeEvent(WindowResizeEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
	private:
		// Main_Scene
		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_MenuScene;

		// Menu Scene 
		Entity e_MenuCamera;
		Entity e_Title;
		Entity e_MenuBG;

		// Main Scene 
		std::vector<Entity> e_Pillars;
		Ref<Texture2D> t_PillarsTexture;
		Entity e_Player;
		Entity e_Camera;
		Entity e_Ceiling;
		Entity e_BG;
		Entity e_Floor;

		// GameMode Parameters
		GameState m_GameState = GameState::GAMEOVER;

		// ImGui
		ImFont* m_Font;

	};

}

