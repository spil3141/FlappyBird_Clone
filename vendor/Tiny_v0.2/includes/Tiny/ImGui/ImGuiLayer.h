#pragma once

#include "Tiny/Core/Layer.h"
#include "Tiny/Core/Timestep.h"
#include "Tiny/Events/Event.h"



namespace Tiny {

	class ImGuiLayer : public Layer // This class should inherit from the Layer class
	{
	public:
		ImGuiLayer(const char* glsl_version);
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

		void OnEvent(Event& e) override;
		void OnUpdate(Timestep dt) override;

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		const char* m_GLSLVersion;
		bool m_BlockEvents = true;
	};

}
