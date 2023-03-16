#pragma once

#include "TinyEngine.h"

class Sandbox2D : public TinyEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(TinyEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(TinyEngine::Event& e) override;
private:
	TinyEngine::OrthographicCameraController m_CameraController;

	// Temp
	TinyEngine::Ref<TinyEngine::VertexArray> m_SquareVA;
	TinyEngine::Ref<TinyEngine::Shader> m_FlatColorShader;
	TinyEngine::Ref<TinyEngine::Texture2D> m_CheckerboardTexture;


	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};