#pragma once
#include "tepch.h"
#include "TinyEngine/Core/Core.h"
#include "TinyEngine/Core/KeyCodes.h"
#include "TinyEngine/Core/MouseCodes.h"

namespace TinyEngine {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}