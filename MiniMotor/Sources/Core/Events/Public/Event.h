#pragma once

#include "mmpch.h"

namespace Sunset
{
	class MM_API KeyEvent
	{
	public:
		int key;

		friend std::ostream& operator<<(std::ostream& os, const KeyEvent& data)
		{
			return os << "Key event : " << data.key;
		}

		bool operator==(const int val)
		{
			return key == val;
		}
	};

	class MM_API MouseEvent
	{
	public:
		float x, y;

		friend std::ostream& operator<<(std::ostream& os, const MouseEvent& data)
		{
			return os << "Mouse event -> x: " << data.x << ", y:" << data.y;
		}
	};

	class MM_API WinCloseEvent
	{

	};

	using Events = std::variant<KeyEvent, MouseEvent, WinCloseEvent>;
}
