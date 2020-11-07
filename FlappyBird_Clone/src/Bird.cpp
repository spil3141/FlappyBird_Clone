#include "Bird.h"

//Third-Party Libraries
#include "ImGui/imgui.h"

std::shared_ptr<Bird> Bird::Create()
{
	return std::make_shared<Bird>();
}

Bird::Bird()
{

}

Bird::~Bird()
{

}

void Bird::OnBegin()
{
	m_BirdTexture = Tiny::Texture2D::Create("res/textures/BirdTexture.png");
}

void Bird::Tick(float Deltatime)
{
	//Vertical Movement
	Velocity.x = m_movementSpeed;

	//TEMP Move Pause, Play, and Space Button Controlls to the GameMode
	//Pause and Space Button
	if (!m_Pause)
	{
		if (Tiny::Input::IsKeyPressed(T_KEY_SPACE))
		{
			Velocity.y += m_JumpForce;

		}else
			Velocity.y -= m_Gravity;
	
		Velocity.y = std::clamp(Velocity.y, -20.0f, 20.1f);
		Position.y += Velocity.y * Deltatime;

		//Horizontal Movement
		Position.x += Velocity.x * Deltatime;
	}

}

void Bird::OnRender()
{
	Tiny::Renderer2D::DrawQuad(Position,glm::radians((Rotation + Velocity.y) * 3.6f), Scale, m_BirdTexture);
}

void Bird::OnImGuiRender()
{
	//ImGui::Begin("Bird Transform");
	////Translation
	//float pos_temp[] = { Position.x,Position.y,Position.z };
	//ImGui::DragFloat3("Translation:", pos_temp, 0.1f);
	//Position.x = pos_temp[0];
	//Position.y = pos_temp[1];
	//Position.z = pos_temp[2];
	////Scale
	//float scale_temp[] = { Scale.x,Scale.y };
	//ImGui::DragFloat2("Scale:", scale_temp, 0.1f);
	//Scale.x = scale_temp[0];
	//Scale.y = scale_temp[1];
	//ImGui::End();

	/*ImGui::Begin("Debug");
	ImGui::DragFloat("Gravity:", &m_Gravity, 0.001f);
	ImGui::DragFloat("JumpForce:", &m_JumpForce, 0.001f);
	ImGui::DragFloat("Movement Speed:", &m_movementSpeed, 0.001f);
	ImGui::Text("");
	ImGui::End();*/


}
