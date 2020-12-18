#pragma once

#include <cmath>

namespace Mathf {

	float lerp(float source, float target, float alpha)
	{
		return source + alpha * (target - source);
	}
}