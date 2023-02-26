#pragma once

#include "tepch.h"

#include "Core.h"

#include "Window.h"
#include "TinyEngine/LayerStack.h"
#include "TinyEngine/Events/Event.h"
#include "TinyEngine/Events/ApplicationEvent.h"

#include "TinyEngine/ImGui/ImGuiLayer.h"

#include "TinyEngine/Renderer/Shader.h"
#include "TinyEngine/Renderer/Buffer.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

	private:
		static Application* s_Instace;
	};
	
	// 在客户端被定义
	Application*  CreateApplication();
}