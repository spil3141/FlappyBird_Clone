#pragma once
#include "Tiny.h"

#include "Bird.h"
#include "Scene.h"

#include "GameObject.h"
#include "ImGui/imgui.h"

#include "Random.h"

class GameMode : public Tiny::Layer
{
public:
	GameMode();
	~GameMode();

	void OnAttach() override;
	void OnDetach() override;


	void OnUpdate(Tiny::Timestep dt) override;
	void OnEvent(Tiny::Event& e) override;
	void OnImGuiRender() override;

	//TEMP Move to Level class
	bool OnKeyPressed(Tiny::KeyPressedEvent& e);
	void ResetLevel();

	void FollowPlayer(Tiny::OrthoCamera& Cam, Tiny::Ref<Bird> player);	
	uint32_t GetPlayerScore() const { return (uint32_t)(Player->GetPosition().x); }

	//Physics
	bool CheckCollisionWithScene(Tiny::Ref<Bird>& player);
	bool PointInTri(const glm::vec2& P, glm::vec2& A, glm::vec2& B, glm::vec2& C);

private:
	Tiny::OrthoCameraController Main_Cam;
	Tiny::Ref<Bird> Player;
	Tiny::Ref<Scene> Scene;

	enum class GameState {
		Playing = 0, GameOver = 1, Paused = 2
	};

	GameState m_GameState = GameState::Paused;
	ImFont* m_Font;

	//ImGui
	bool showDemo = false;
	float frametimes[80] = {};
	int offsetvalue = 0;


	float QuadsOffset = 1.05f;
	int Num_of_Quads = 100;
	int Num_of_Quads_Drawn = 0;
	//float DisplayOffset[];
	float xxx = 0.0f;

};

