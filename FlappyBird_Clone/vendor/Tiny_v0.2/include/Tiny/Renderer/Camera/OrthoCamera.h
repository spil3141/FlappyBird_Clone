#pragma once

#include "Tiny/Renderer/Camera/Camera.h"
#include <string>
#include <glm/glm.hpp>

namespace Tiny {

	class OrthoCamera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

	/*class OrthoCamera : public Camera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float up);
		~OrthoCamera();

		void SetProjection(float left, float right, float bottom, float up);

		void SetPerspectiveMatrix(const glm::mat4& newperspectivematrix);
		
		virtual const glm::mat4& GetViewMatrix() const override;
		virtual const glm::vec3& GetPosition() const override;
		virtual const glm::mat4& GetProjectionViewMatrix() const override;

		virtual void SetViewMatrix(const glm::mat4& newviewmatrix) override;
		virtual void SetPostion(const glm::vec3& newPostion) override;
		

		virtual inline std::string GetName() const override { return m_Name; };

		void ReCalculatePVMatrix() override;
	

	private:
		glm::vec3 m_Position;

		glm::mat4 m_ProspectiveViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	};*/
}