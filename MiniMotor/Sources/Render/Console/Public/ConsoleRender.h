// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericRender.h"

class ConsoleRender : public GenericRender<ConsoleRender>
{
	using type = std::array<std::string, 80*40>;

public:

	void Init();

	void HandleEvents();

	void Draw() const;

	bool IsWindowOpen();

	void ClearWindow();

	void BufferFrame(const VertexArray2D& targetEntity);

	void CloseWindow();

private:

	type m_Image;

	int i = 0;
};

