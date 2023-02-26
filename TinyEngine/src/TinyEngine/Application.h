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
#include "TinyEngine/Renderer/VertexArray.h"

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
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instace;
	};
	
	// 在客户端被定义
	Application*  CreateApplication();
}