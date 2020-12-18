#pragma once

#include "glm/glm.hpp"

namespace Tiny {

	class DebugPhysics
	{
	public:
		static bool PointInTri(const glm::vec2& P, glm::vec2& A, glm::vec2& B, glm::vec2& C);
	};
}