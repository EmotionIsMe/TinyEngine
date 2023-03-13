#include "tepch.h"
#include "LayerStack.h"

namespace TinyEngine {


	LayerStack::LayerStack() {

	}
	
	LayerStack::~LayerStack() {
		
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}
	
	void LayerStack::PushLayer(Layer* layer) {

		//  ��ָ��λ��֮ǰ����Ԫ��
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}
	
	void LayerStack::PushOverlay(Layer* overlay) {

		//  ��β������Ԫ��
		m_Layers.emplace_back(overlay);
	}
	
	
	void LayerStack::PopLayer(Layer* layer) {

		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}
	
	void LayerStack::PopOverlay(Layer* overlay) {

		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}