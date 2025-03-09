#pragma once

namespace Sunset
{
	struct MM_API Inputs
	{
		static bool IsKeyPressed(int32_t key);
		static bool IsKeyReleased(int32_t key);
		static bool IsMouseButtonPressed(int32_t button);
		static glm::vec2 GetMousePosition();
	};
}
