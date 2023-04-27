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
		
		virtual void  OnAttach() {}					//当layer添加到layer stack的时候会调用此函数，相当于Init函数
		virtual void  OnDetach() {}					//当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
		virtual void  OnUpdate(Timestep ts) {}		//用于处理渲染的loop
		virtual void  OnImGuiRender() {}
		virtual void  OnEvent(Event& event) {}		//用于接受外部的Event

		inline const std::string &GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};

}

