// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "GenericRender.h"

class MM_EXPORT OpenGLRender : public GenericRender<OpenGLRender>
{
public:

	void Init();

	void Update();

	void Draw();

	bool IsWindowOpen() const;

	void BufferFrame(const VertexArray2D& Entity);

	void HandleEvents();

	void ClearWindow();

	void CloseWindow();

	void DrawSlate(class SContainer* slate);
};