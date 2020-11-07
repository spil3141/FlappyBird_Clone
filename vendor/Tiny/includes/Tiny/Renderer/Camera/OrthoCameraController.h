#pragma once

#include "Tiny/Renderer/Camera/CameraController.h"
#include "Tiny/Renderer/Camera/OrthoCamera.h"

#include "Tiny/Events/MouseEvent.h"
#include "Tiny/Events/ApplicationEvent.h"

namespace Tiny{
	
	class OrthoCameraController : public CameraController
	{
	public:
		OrthoCameraController(float AspectRatio);
		~OrthoCameraController();

		inline OrthoCamera& GetCamera() { return m_Camera; }

		void OnUpdate(Timestep dt) override;
		void OnEvent(Event& e) override;

		inline void SetZoom(const float value) { m_Zoom = value; }
		inline float GetZoom() const { return m_Zoom; }

		void Recalibrate();

		bool OnMouseScroll(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);
	private:

		float m_Zoom = 1.0f;
		float m_AspectRatio;
		glm::vec3 cam_pos = { 0.0f,0.0f,0.0f };

		float m_CameraTranslationSpeed = 10.0f;
		//float m_CameraRotation = 0.0f;


		OrthoCamera m_Camera;
	};
}

