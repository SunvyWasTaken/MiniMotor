// Copyright Shimmer Studios : All rights reserved.

#include "GenericRender.h"
#ifdef USE_SFML
class MM_EXPORT SFMLRender : public GenericRender<SFMLRender>
{
public:
	
	void Init();

	void Update();

	bool IsWindowOpen() const;

	void CloseWindow();

	void BindEvents(const EventsCallback& events);

	void DrawObject(const VertexArray2D& vertexArray);
};
#endif
