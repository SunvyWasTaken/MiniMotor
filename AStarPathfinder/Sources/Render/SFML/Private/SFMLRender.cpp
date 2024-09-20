
#include "SFMLRender.h"

#include "Debug/Debug.h"
#include "Entitys.h"
#include "Setting.h"
#include "Utils/StateMachine.h"

#include <SFML/Graphics.hpp>

#include <variant>

#define CellSize 10

#define WindowSize 850

namespace
{
	sf::RenderWindow Window;

	sf::Font font;

	void DrawQuad2D(FQuad2D& obj)
	{
		sf::RectangleShape rectangle(sf::Vector2f(obj.transform.scale.x * CellSize, obj.transform.scale.y * CellSize));
		rectangle.setPosition(obj.transform.pos.x * CellSize, obj.transform.pos.y * CellSize);
		Window.draw(rectangle);
	}

	void DrawVertexArray(VertexArray2D& obj)
	{
		sf::VertexArray vertexArray(sf::Quads, obj->size());
		for (uint64_t index = 0; index < obj->size(); ++index)
		{
			uint64_t i = index * 4;

			vertexArray[i + 0].position = sf::Vector2f(obj[i].GetVerticePosition<Side::TopLeft>().x, obj[i].GetVerticePosition<Side::TopLeft>().y);
			vertexArray[i + 1].position = sf::Vector2f(obj[i].GetVerticePosition<Side::TopRight>().x, obj[i].GetVerticePosition<Side::TopRight>().y);
			vertexArray[i + 2].position = sf::Vector2f(obj[i].GetVerticePosition<Side::BottomRight>().x, obj[i].GetVerticePosition<Side::BottomRight>().y);
			vertexArray[i + 3].position = sf::Vector2f(obj[i].GetVerticePosition<Side::BottomLeft>().x, obj[i].GetVerticePosition<Side::BottomLeft>().y);

			vertexArray[i + 0].color = sf::Color(obj[i].GetVertice<Side::TopLeft>().color.r, obj[i].GetVertice<Side::TopLeft>().color.g, obj[i].GetVertice<Side::TopLeft>().color.b, obj[i].GetVertice<Side::TopLeft>().color.a);
			vertexArray[i + 1].color = sf::Color(obj[i].GetVertice<Side::TopRight>().color.r, obj[i].GetVertice<Side::TopLeft>().color.g, obj[i].GetVertice<Side::TopLeft>().color.b, obj[i].GetVertice<Side::TopLeft>().color.a);
			vertexArray[i + 2].color = sf::Color(obj[i].GetVertice<Side::BottomRight>().color.r, obj[i].GetVertice<Side::TopLeft>().color.g, obj[i].GetVertice<Side::TopLeft>().color.b, obj[i].GetVertice<Side::TopLeft>().color.a);
			vertexArray[i + 3].color = sf::Color(obj[i].GetVertice<Side::BottomLeft>().color.r, obj[i].GetVertice<Side::TopLeft>().color.g, obj[i].GetVertice<Side::TopLeft>().color.b, obj[i].GetVertice<Side::TopLeft>().color.a);
		}
		Window.draw(vertexArray);
	}
}

void SFMLRender::Init()
{
	Window.create(sf::VideoMode(WindowSize, WindowSize), "SFML works!");
	ensure(Window);
	ensure(font.loadFromFile("Ressources/PoiretOne-Regular.ttf"));
}

void SFMLRender::HandleEvent()
{
	sf::Event event;
	while (Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			Window.close();

		if(event.type == sf::Event::Resized)
		{
			float ratio = (float)event.size.width / (float)event.size.height;
			sf::View view = Window.getView();
			view.setSize(WindowSize * ratio, WindowSize);
			Window.setView(view);
		}
	}
}

void SFMLRender::Draw()
{
	Window.display();
}

bool SFMLRender::IsWindowOpen()
{
	return Window.isOpen();
}

void SFMLRender::BufferFrame(Entity* Entity)
{
	for (auto drawable : Entity->drawables)
	{
		std::visit(overloaded(
			[&](FQuad2D& obj)
			{
				DrawQuad2D(obj);
			}, 
			[&](VertexArray2D& obj)
			{
				DrawVertexArray(obj);
			}
			), drawable);
	}
}

void SFMLRender::ClearWindow()
{
	Window.clear();
}

void SFMLRender::CloseWindow()
{
	Window.close();
}
