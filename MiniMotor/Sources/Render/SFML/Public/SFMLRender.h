// Copyright Shimmer Studios : All rights reserved.

#include "GenericRender.h"

#if RENDERTYPE == 1

class MM_EXPORT SFMLRender : public GenericRender<SFMLRender>
{
public:
	
	void Init();

	void Update();

	void Draw();

	bool IsWindowOpen() const;

	void BufferFrame(const VertexArray2D& vertexArray);

	void HandleEvents();

	void ClearWindow();

	void CloseWindow();

	void DrawSlate(class SContainer* slate);
};

#endif
