
#include "tepch.h"
#include "Application.h"

#include "TinyEngine/Renderer/Renderer.h"

#include "Input.h"

#include <glfw/glfw3.h>

namespace TinyEngine {

	#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)


	Application* Application::s_Instace = nullptr;

	Application::Application() {

		TE_CORE_ASSERT(!s_Instace, "Application already exists");
		s_Instace = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}
	Application::~Application() {
		
	}

	void Application::PushLayer(Layer* layer) {
		
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay) {
		
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::onEvent(Event& e) {
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end();it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e){
		m_Running = false;
		return true;
	}

	void Application::Run() {

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

}

