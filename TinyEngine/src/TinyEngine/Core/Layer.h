#pragma once

#include "TinyEngine/Core/Core.h"
#include "TinyEngine/Events/Event.h"

#include "TinyEngine/Core/Timestep.h"

namespace TinyEngine {
	class TE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		
		virtual void  OnAttach() {}					//��layer��ӵ�layer stack��ʱ�����ô˺������൱��Init����
		virtual void  OnDetach() {}					//��layer��layer stack�Ƴ���ʱ�����ô˺������൱��Shutdown����
		virtual void  OnUpdate(Timestep ts) {}		//���ڴ�����Ⱦ��loop
		virtual void  OnImGuiRender() {}
		virtual void  OnEvent(Event& event) {}		//���ڽ����ⲿ��Event

		inline const std::string &GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};

}

