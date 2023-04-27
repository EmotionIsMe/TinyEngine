#include "tepch.h"
#include "OrthographicCameraController.h"

#include "TinyEngine/Core/Input.h"
#include "TinyEngine/Core/KeyCodes.h"


namespace TinyEngine {


	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}


	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		TE_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(Key::A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;


		if (Input::IsKeyPressed(Key::W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;


		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;


			m_Camera.SetRotation(m_CameraRotation);
		}


		m_Camera.SetPosition(m_CameraPosition);


		m_CameraTranslationSpeed = m_ZoomLevel;
	}


	void OrthographicCameraController::OnEvent(Event& e)
	{
		TE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(TE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(TE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	// 当窗口调整大小时, 改变相机可以看到的区域
	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		// 里面会调用glm::ortho(float left, float right, float bottom, float top)函数
		// 根据这段代码可知, camera看到的区域高度不会随着窗口大小而改变
		// 而是会随着鼠标滚动改变zoom值而变化
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		TE_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}


	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		TE_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}