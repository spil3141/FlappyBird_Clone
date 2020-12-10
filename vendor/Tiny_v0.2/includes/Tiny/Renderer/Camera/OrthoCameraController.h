#pragma once

#include "Tiny/Renderer/Camera/OrthoCamera.h"

#include "Tiny/Events/MouseEvent.h"
#include "Tiny/Events/ApplicationEvent.h"

namespace Tiny{
	
	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthoCamera& GetCamera() { return m_Camera; }
		const OrthoCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthoCamera m_Camera;

		bool m_Rotation;

		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};



	//class OrthoCameraController : public CameraController
	//{
	//public:
	//	OrthoCameraController(float AspectRatio);
	//	~OrthoCameraController();

	//	inline OrthoCamera& GetCamera() { return m_Camera; }

	//	void OnUpdate(Timestep dt) override;
	//	void OnEvent(Event& e) override;

	//	inline void SetZoom(const float value) { m_Zoom = value; }
	//	inline float GetZoom() const { return m_Zoom; }

	//	void Recalibrate();
	//	void Resize(float width, float height);

	//	bool OnMouseScroll(MouseScrolledEvent& event);
	//	bool OnWindowResized(WindowResizeEvent& event);
	//private:

	//	float m_Zoom = 1.0f;
	//	float m_AspectRatio;
	//	glm::vec3 cam_pos = { 0.0f,0.0f,0.0f };

	//	float m_CameraTranslationSpeed = 10.0f;
	//	//float m_CameraRotation = 0.0f;


	//	OrthoCamera m_Camera;
	//};
}

