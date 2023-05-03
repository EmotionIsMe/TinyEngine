#pragma once

#include "tepch.h"

#include "Core.h"

#include "Window.h"
#include "TinyEngine/Core/LayerStack.h"
#include "TinyEngine/Events/Event.h"
#include "TinyEngine/Events/ApplicationEvent.h"

#include "TinyEngine/Core/Timestep.h"

#include "TinyEngine/ImGui/ImGuiLayer.h"

namespace TinyEngine {

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			TE_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	// 创建一个Application类代表游戏基类
	// 一个游戏只需要有一个LayerStack，用于存放多个Layer
	class  Application
	{
	public:
		Application(const std::string& name = "TinyEngine App", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		virtual ~Application();
		
		void Run();
		void onEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return  *m_Window; }

		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationCommandLineArgs m_CommandLineArgs;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instace;
	};
	
	// 在客户端被定义
	Application* CreateApplication(ApplicationCommandLineArgs args);
}