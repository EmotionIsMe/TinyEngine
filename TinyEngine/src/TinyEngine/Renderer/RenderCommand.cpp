#include "tepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace TinyEngine {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}