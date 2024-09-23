
#include "GenericRender.h"

class MM_EXPORT SFMLRender : public GenericRender<SFMLRender>
{
public:
	
	void Init();

	void HandleEvent();

	void Draw();

	bool IsWindowOpen();

	void BufferFrame(class Entity* Entity);

	void ClearWindow();

	void CloseWindow();
};
