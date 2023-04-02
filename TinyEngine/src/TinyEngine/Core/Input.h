#pragma once
#include "tepch.h"
#include "TinyEngine/Core/Core.h"
#include "TinyEngine/Core/KeyCodes.h"
#include "TinyEngine/Core/MouseButtonCodes.h"

namespace TinyEngine {

	class TE_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}