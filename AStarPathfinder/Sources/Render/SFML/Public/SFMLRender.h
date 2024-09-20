
#include "GenericRender.h"

#include <memory>

class SFMLRender : public GenericRender<SFMLRender>
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
