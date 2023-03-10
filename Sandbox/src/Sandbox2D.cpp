#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = TinyEngine::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	TinyEngine::Ref<TinyEngine::VertexBuffer> squareVB;
	squareVB.reset(TinyEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ TinyEngine::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	TinyEngine::Ref<TinyEngine::IndexBuffer> squareIB;
	squareIB.reset(TinyEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = TinyEngine::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(TinyEngine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	TinyEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	TinyEngine::RenderCommand::Clear();

	TinyEngine::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<TinyEngine::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<TinyEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	TinyEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	TinyEngine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(TinyEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}