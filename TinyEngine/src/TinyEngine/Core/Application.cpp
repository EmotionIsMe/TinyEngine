
#include "tepch.h"
#include "Application.h"

#include "TinyEngine/Renderer/Renderer.h"
#include "TinyEngine/Scripting/ScriptEngine.h"
#include "Input.h"

#include <glfw/glfw3.h>

namespace TinyEngine {

	// std::bind第一个参数是函数指针, 第二个代表的类对象(因为是类的成员函数)
	// 第三个代表的是放到函数的第一位
	#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::s_Instace = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		TE_PROFILE_FUNCTION();

		TE_CORE_ASSERT(!s_Instace, "Application already exists");
		s_Instace = this;

		// Set working directory here
		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		m_Window = Window::Create(WindowProps(m_Specification.Name));

		// 这里会设置m_Window里的std::function<void(Event&)>对象, 当接受Event时, 会调用Application::OnEvent函数
		m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));	// 设置window的callback为此对象的OnEvent函数

		Renderer::Init();
		ScriptEngine::Init();

		// Application应该自带ImGuiLayer, 这段代码应该放到引擎内部而不是User的Application派生类里
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}
	Application::~Application() 
	{
		TE_PROFILE_FUNCTION();

		ScriptEngine::Shutdown();
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

	void Application::Close()
	{
		m_Running = false;
	}

	// 当窗口触发事件时, 会调用此函数
	void Application::onEvent(Event& e) 
	{
		TE_PROFILE_FUNCTION();

		// 1. 当接受窗口来的Event时, 首先判断是否是窗口关闭的事件
		// Dispatch函数只有在Event类型跟模板T匹配时, 才响应事件
		// std::bind其实是把函数和对应的参数绑定的一起
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		// 2. 否则才传递到layer来执行事件, 逆序遍历是为了让ImGuiLayer最先收到Event
		// 从后向前检查事件是否被处理
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

				m_ImGuiLayer->Begin(); //统一调用，调用了NewFrame
				{
					TE_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
					
				}
				m_ImGuiLayer->End(); //统一结束调用，调用了EndFrame
			}

			// 创建完window后，直接调用loop进行渲染
			// 每帧结束调用glSwapBuffer
			m_Window->OnUpdate();
		}
	}

}

