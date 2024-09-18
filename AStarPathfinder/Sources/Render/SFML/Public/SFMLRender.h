
#include "IRender.h"

#include <memory>
#include <SFML/Graphics.hpp>

class SFMLRender : public IDraw<SFMLRender>
{
public:
	void Init();

	void HandleEvent();

	void Draw();

	bool IsWindowOpen();

	void BufferFrame(size_t index, class IEntity* Entity);

	void ClearWindow();

	void CloseWindow();

private:

	struct MyContainer
	{
		static MyContainer* GetValue();

		static MyContainer* SelfPtr;

		static void DestroyContainer();

		std::unique_ptr<sf::RenderWindow> Window;

		sf::VertexArray Rectangle;

		sf::Clock clock;

		sf::Font font;

	private:
		MyContainer() {}
		MyContainer(const MyContainer&) = delete;
		MyContainer& operator=(const MyContainer&) = delete;
	};
};

using SFMLDraw = IDraw<SFMLRender>;