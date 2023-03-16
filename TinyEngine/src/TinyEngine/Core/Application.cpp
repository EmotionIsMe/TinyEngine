
#include "tepch.h"
#include "Application.h"

#include "TinyEngine/Renderer/Renderer.h"

#include "Input.h"

#include <glfw/glfw3.h>

namespace TinyEngine {

	#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::s_Instace = nullptr;

	Application::Application() 
	{
		TE_PROFILE_FUNCTION();

		TE_CORE_ASSERT(!s_Instace, "Application already exists");
		s_Instace = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}
	Application::~Application() 
	{
		TE_PROFILE_FUNCTION();

		Renderer::Shutdown();
		
	}

	void Application::PushLayer(Layer* layer) 
	{
		TE_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay) 
	{
		TE_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::onEvent(Event& e) 
	{
		TE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end();it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		TE_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::Run() 
	{
		TE_PROFILE_FUNCTION();

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) 
			{
				{
					TE_PROFILE_SCOPE("RunLoop");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					TE_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
					m_ImGuiLayer->End();
				}
			}

			m_Window->OnUpdate();
		}
	}

}

