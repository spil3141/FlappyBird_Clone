#pragma once

#include "Tiny/Events/Event.h"
#include "Tiny/Core/Timestep.h"

namespace Tiny {

	class CameraController
	{
	public:
		virtual ~CameraController() = default;

		virtual void OnUpdate(Timestep dt) = 0;
		virtual void OnEvent(Event& e) = 0;


	};

}
