
#include "tepch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

namespace TinyEngine {

	#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)


	Application* Application::s_Instace = nullptr;

	Application::Application() {

		TE_CORE_ASSERT(!s_Instace, "Application already exists");
		s_Instace = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));

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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

}

