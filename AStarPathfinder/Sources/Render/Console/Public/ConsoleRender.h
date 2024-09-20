#pragma once

#include "GenericRender.h"
#include "Setting.h"

#include <string>

class ConsoleRender : public GenericRender<ConsoleRender>
{
	using type = std::string[GRID_SIZE_X + 1][GRID_SIZE_Y + 1];

public:

	void Init();

	void HandleEvent();

	void Draw() const;

	bool IsWindowOpen();

	void ClearWindow();

	void BufferFrame(size_t index, class Entity* targetEntity);

	void CloseWindow();

private:

	type m_Image;

	int i = 0;
};

