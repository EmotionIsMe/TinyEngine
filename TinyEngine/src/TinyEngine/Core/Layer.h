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
		
		virtual void  OnAttach() {}
		virtual void  OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void  OnImGuiRender() {}
		virtual void  OnEvent(Event& event) {}

		inline const std::string &GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};

}

