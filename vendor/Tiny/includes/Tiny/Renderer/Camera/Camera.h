#pragma once

#include <string>
#include "glm/glm.hpp"
#include "Tiny/Core/Timestep.h"
#include "Tiny/Events/Event.h"

namespace Tiny {

	class Camera
	{
	public:
		virtual ~Camera() = default;


		virtual void SetViewMatrix(const glm::mat4& newviewmatrix) = 0;
		virtual void SetPostion(const glm::vec3& newPostion) = 0;

		virtual const glm::mat4& GetProjectionViewMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::vec3& GetPosition() const = 0;

		virtual std::string GetName() const = 0;
		
	protected:
		virtual void ReCalculatePVMatrix() = 0;

	public:
		std::string m_Name = "Tiny Camera";




	};
}







	
		//virtual void OnUpdate(Timestep dt) = 0;
		////This is a Build-in Camera Controller
		//virtual void OnEvent(Event& e) = 0;
