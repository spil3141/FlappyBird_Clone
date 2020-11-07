#pragma once

#include <vector>
#include "Tiny/Core/Layer.h"

namespace Tiny {
	
	class LayerStack
	{
	public:
		LayerStack() = default;  //initialize the m_LayerInsert variable
		~LayerStack(); //delete all the layer pointers in the vector

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layeroverlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layeroverlay);

		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0 ;

	};
}
