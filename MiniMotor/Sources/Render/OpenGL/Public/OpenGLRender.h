
#pragma once

#include "GenericRender.h"

class MM_EXPORT OpenGLRender : public GenericRender<OpenGLRender>
{
public:

	void Init();

	void HandleEvents();

	void Draw();

	bool IsWindowOpen();

	void BufferFrame(class Entity* Entity);

	void ClearWindow();

	void CloseWindow();
};