#pragma once

#include "entt.hpp"
#include "Tiny/Core/Timestep.h"

namespace Tiny {
	
	class Entity;
		
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name = std::string());
		
		void OnUpdate(Timestep dt);
		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
	};
}

