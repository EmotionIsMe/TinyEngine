#pragma once

#include "TinyEngine/Core/Core.h"
#include "Layer.h"
#include <vector>

namespace TinyEngine {

	class TE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		
		void PushLayer(Layer* layer);		//lay 代表普通的layer, Overlay代表离屏幕最远的layer
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}
