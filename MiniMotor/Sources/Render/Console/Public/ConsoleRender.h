#pragma once

#include "CoreMinimal.h"
#include "GenericRender.h"

class ConsoleRender : public GenericRender<ConsoleRender>
{
	using type = std::string[81][41];

public:

	void Init();

	void HandleEvents();

	void Draw() const;

	bool IsWindowOpen();

	void ClearWindow();

	void BufferFrame(class Entity* targetEntity);

	void CloseWindow();

private:

	type m_Image;

	int i = 0;
};

