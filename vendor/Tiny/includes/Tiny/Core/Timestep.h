#pragma once 

#include "Tiny/Core/Time.h"

namespace Tiny {

	class Timestep {
	public:
		Timestep(float time = 0.0f) : m_Time(time) {};
		~Timestep() {};

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }

		operator float() const { return m_Time; } //This function is called when you try to implicitly convert from this object to a float.

		inline double GetTimeSinceStartup() { return Time::Fixedtime(); }

	private:
		float m_Time;
	};
}