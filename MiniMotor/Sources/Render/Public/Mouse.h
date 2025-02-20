#pragma once

#include <variant>

namespace Sunset
{
	// Capture methode
	namespace Cursor
	{
		struct Normal {};
		struct Hidden {};
		struct Disable {};
		struct Captured {};

		using CursorState = std::variant<Normal, Hidden, Disable, Captured>;
	}
}
