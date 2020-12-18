#pragma once

#include <string.h>

#include "Tiny/Events/Event.h"
#include "Tiny/Core/Timestep.h"

namespace Tiny {

	class Layer
	{
	public:
		Layer(const std::string name = "Tiny Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep dt) {};
		virtual void OnEvent(Event& e) {};

		virtual void OnImGuiRender() {}

		inline const std::string Getname() const { return m_Layername; }
	private:
		std::string m_Layername;
	};

}
