#include "tepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace TinyEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		TE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		TE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TE_CORE_ASSERT(status, "Failed to initialize Glad!");

		TE_CORE_INFO("OpenGL Info:");
		TE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		TE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		TE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		TE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}