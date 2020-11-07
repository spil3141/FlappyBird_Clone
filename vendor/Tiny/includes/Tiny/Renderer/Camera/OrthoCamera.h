#pragma once

#include "Tiny/Renderer/Camera/Camera.h"
#include <string>
#include "glm/glm.hpp"

namespace Tiny {

	class OrthoCamera : public Camera
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
	};
}