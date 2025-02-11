#pragma once

class KeyEvent
{
	using uint = unsigned int;
public:
	uint key;

	friend std::ostream& operator<<(std::ostream& os, const KeyEvent& data)
	{
		return os << "Key event : " << data.key;
	}

	bool operator==(const uint val)
	{
		return key == val;
	}
};

class MouseEvent
{
public:
	float x, y;

	friend std::ostream& operator<<(std::ostream& os, const MouseEvent& data)
	{
		return os << "Mouse event -> x: " << data.x << ", y:" << data.y;
	}
};

template <typename ...Ts>
struct Overloaded : Ts...
{
	using Ts::operator()...;
};

template <class ...Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

using Events = std::variant<KeyEvent, MouseEvent>;
