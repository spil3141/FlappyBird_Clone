#pragma once

#include "Tiny/Events/KeyCodes.h"
#include "Tiny/Events/MouseCodes.h"
#include "glm/glm.hpp"

namespace Tiny {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool HasKeyBeenReleased(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}