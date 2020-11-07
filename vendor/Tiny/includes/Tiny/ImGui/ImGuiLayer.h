#pragma once

#include "Tiny/Core/Layer.h"
#include "Tiny/Core/Timestep.h"
#include "Tiny/Events/Event.h"



namespace Tiny {

	class ImGuiLayer : public Layer // This class should inherit from the Layer class
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();


		void OnEvent(Event& e) override;


		void OnUpdate(Timestep dt) override;

	private:
		const char* glsl_version;
		bool m_BlockEvents = true;
	};

}
