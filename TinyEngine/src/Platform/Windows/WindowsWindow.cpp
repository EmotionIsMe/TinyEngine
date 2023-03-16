#include "tepch.h"
#include "TinyEngine/Core/Core.h"
#include "WindowsWindow.h"

#include "TinyEngine/Events/ApplicationEvent.h"
#include "TinyEngine/Events/KeyEvent.h"
#include "TinyEngine/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace TinyEngine {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallbak(int error, const char* description) 
	{	
		TE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		TE_PROFILE_FUNCTION();

		Init(props);
	}

	// APP.cpp 中m_window调用create的时候会走到这里来
	// 之后可以用宏来判断到底是链接到哪个平台来实现
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		TE_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		TE_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		TE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			TE_PROFILE_SCOPE("glfwInit");

			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			TE_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallbak);
			s_GLFWInitialized = true;
		}

		{
			TE_PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		}
		
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callback
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowResizeEvent event(width, height);
			data.Width = width;
			data.Height = height;
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window,int key,int scancode,int action,int mods) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS: 
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				default:
						break;
				}
		});

		// key typed
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) 
		{

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			default:
				break;
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffeset, double yOffset)
		{

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffeset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		TE_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		TE_PROFILE_FUNCTION();

		// 窗口操作的时候会调用glfwPollEvents 并且对事件进行一个内部判断
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		TE_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
