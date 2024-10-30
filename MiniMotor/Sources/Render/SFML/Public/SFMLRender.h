// Copyright Shimmer Studios : All rights reserved.

#include "GenericRender.h"
#ifdef USE_SFML
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

	void DrawLine(const FVec2& start, const FVec2& end, const FColor& color);

	void DrawQuad(const FVec2& position, const FVec2& size, const FColor& color);
};
#endif
