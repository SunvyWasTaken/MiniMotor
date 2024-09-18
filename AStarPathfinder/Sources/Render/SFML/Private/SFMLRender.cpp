
#include "SFMLRender.h"

#include "Entitys.h"
#include "Setting.h"
#include "Terrain.h"

#include "Debug.h"

#define CellSize 4
#define WindowSize 850

void SFMLRender::Init()
{
	MyContainer::GetValue()->Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WindowSize, WindowSize), "SFML works!");
	MyContainer::GetValue()->Rectangle.setPrimitiveType(sf::Quads);
	MyContainer::GetValue()->Rectangle.resize(4 * World->TerrainGrid.size());
	ensure(MyContainer::GetValue()->font.loadFromFile("Ressources/PoiretOne-Regular.ttf"));
}

void SFMLRender::HandleEvent()
{
	sf::Event event;
	while (MyContainer::GetValue()->Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			MyContainer::GetValue()->Window->close();

		if(event.type == sf::Event::Resized)
		{
			float ratio = (float)event.size.width / (float)event.size.height;
			sf::View view = MyContainer::GetValue()->Window->getView();
			view.setSize(WindowSize * ratio, WindowSize);
			MyContainer::GetValue()->Window->setView(view);
		}
	}
}

void SFMLRender::Draw()
{
	sf::Time ElapseTime = MyContainer::GetValue()->clock.restart();
	int FPS = static_cast<int>(1.f / ElapseTime.asSeconds());
	std::string FPSString = "Fps : " + std::to_string(FPS);
	sf::Text text{FPSString, MyContainer::GetValue()->font};
	MyContainer::GetValue()->Window->draw(MyContainer::GetValue()->Rectangle);
	MyContainer::GetValue()->Window->draw(text);
	MyContainer::GetValue()->Window->display();
}

bool SFMLRender::IsWindowOpen()
{
	return MyContainer::GetValue()->Window->isOpen();
}

void SFMLRender::BufferFrame(size_t index, class IEntity* Entity)
{
	size_t i = index * 4;
	MyContainer::GetValue()->Rectangle[i + 0].position = sf::Vector2f(static_cast<float>((Entity->Location.x * CellSize) + (CellSize/2)), static_cast<float>(Entity->Location.y * CellSize) + (CellSize/2));
	MyContainer::GetValue()->Rectangle[i + 1].position = sf::Vector2f(static_cast<float>(((Entity->Location.x * CellSize) + (CellSize/2)) + CellSize), static_cast<float>(Entity->Location.y * CellSize) + (CellSize/2));
	MyContainer::GetValue()->Rectangle[i + 2].position = sf::Vector2f(static_cast<float>((Entity->Location.x * CellSize) + (CellSize/2) + CellSize), static_cast<float>((Entity->Location.y * CellSize) + CellSize + (CellSize/2)));
	MyContainer::GetValue()->Rectangle[i + 3].position = sf::Vector2f(static_cast<float>((Entity->Location.x * CellSize) + (CellSize/2)), static_cast<float>((Entity->Location.y * CellSize) + CellSize) + (CellSize/2));

	sf::Color color = (Entity->IsCell() ? sf::Color::Black : sf::Color::Blue);

	MyContainer::GetValue()->Rectangle[i + 0].color = color;
	MyContainer::GetValue()->Rectangle[i + 1].color = color;
	MyContainer::GetValue()->Rectangle[i + 2].color = color;
	MyContainer::GetValue()->Rectangle[i + 3].color = color;
}

void SFMLRender::ClearWindow()
{
	MyContainer::GetValue()->Window->clear();
	//MyContainer::GetValue()->Rectangle.clear();
	//MyContainer::GetValue()->Rectangle.setPrimitiveType(sf::Quads);
	//MyContainer::GetValue()->Rectangle.resize(4 * World->TerrainGrid.size());
}

void SFMLRender::CloseWindow()
{
	MyContainer::GetValue()->Window->close();
	MyContainer::DestroyContainer();
}

SFMLRender::MyContainer* SFMLRender::MyContainer::GetValue()
{
	if (!SelfPtr)
	{
		SelfPtr = new MyContainer();
	}
	return SelfPtr;
}

void SFMLRender::MyContainer::DestroyContainer()
{
	if (SelfPtr)
	{
		delete SelfPtr;
		SelfPtr = nullptr;
	}
}

SFMLRender::MyContainer* SFMLRender::MyContainer::SelfPtr = nullptr;
