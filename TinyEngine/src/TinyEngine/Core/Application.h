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

	struct ApplicationSpecification {
		std::string Name = "Game Engine Application"; // Ĭ�����г�������
		std::string WorkingDirectory;				// ����Ŀ¼
		ApplicationCommandLineArgs CommandLineArgs;

	};

	// ����һ��Application�������Ϸ����
	// һ����Ϸֻ��Ҫ��һ��LayerStack�����ڴ�Ŷ��Layer
	class  Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();
		
		void Run();
		void onEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return  *m_Window; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationSpecification m_Specification;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instace;
	};
	
	// �ڿͻ��˱�����
	Application* CreateApplication(ApplicationCommandLineArgs args);
}