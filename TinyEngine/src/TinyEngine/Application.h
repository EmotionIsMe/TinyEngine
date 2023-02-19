#pragma once

#include "tepch.h"

#include "Core.h"

#include "Window.h"
#include "TinyEngine/LayerStack.h"
#include "TinyEngine/Events/Event.h"
#include "TinyEngine/Events/ApplicationEvent.h"

namespace TinyEngine {

	class  TE_API  Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		void onEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return  *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instace;
	};
	
	// 在客户端被定义
	Application*  CreateApplication();
}