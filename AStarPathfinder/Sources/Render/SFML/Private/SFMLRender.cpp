
#include "SFMLRender.h"

#include "Entitys.h"
#include "Setting.h"
#include "Terrain.h"

#define CellSize 15

void SFMLRender::Init()
{
	MyContainer::GetValue()->Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 800), "SFML works!");
	MyContainer::GetValue()->Rectangle.setPrimitiveType(sf::Quads);
	MyContainer::GetValue()->Rectangle.resize(4 * World->TerrainGrid.size());
}

void SFMLRender::Draw()
{
	MyContainer::GetValue()->Window->draw(MyContainer::GetValue()->Rectangle);
	MyContainer::GetValue()->Window->display();
}

bool SFMLRender::IsWindowOpen()
{
	return MyContainer::GetValue()->Window->isOpen();
}

void SFMLRender::BufferFrame(class IEntity* Entity)
{
	
	MyContainer::GetValue()->Rectangle.append(sf::Vertex(sf::Vector2f(Entity->Location.x * CellSize, Entity->Location.y * CellSize), (Entity->IsCell() ? sf::Color::Green : sf::Color::Red)));

}

void SFMLRender::ClearWindow()
{
	MyContainer::GetValue()->Window->clear();
	MyContainer::GetValue()->Rectangle.resize(4 * World->TerrainGrid.size());
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
