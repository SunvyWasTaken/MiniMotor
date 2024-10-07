// Copyright Shimmer Studios : All rights reserved.

#include "GenericRender.h"

class MM_EXPORT SFMLRender : public GenericRender<SFMLRender>
{
public:
	
	void Init();

	void Update();

	void Draw();

	bool IsWindowOpen();

	void BufferFrame(const VertexArray2D& vertexArray);

	void HandleEvents();

	void ClearWindow();

	void CloseWindow();

	void DrawSlate(class SContainer* slate);
};
