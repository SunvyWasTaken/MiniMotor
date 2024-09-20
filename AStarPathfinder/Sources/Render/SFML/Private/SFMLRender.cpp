
#include "SFMLRender.h"

#include "Debug/Debug.h"
#include "Entitys.h"
#include "Setting.h"
#include "Utils/StateMachine.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
#include <variant>

#define CellSize 10

#define WindowSize 850

// This is a private
namespace
{
	static sf::RenderWindow Window;

	static sf::Font font;

	void DrawQuad2D(FQuad2D& obj)
	{
		sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(obj.transform.scale.x * CellSize), static_cast<float>(obj.transform.scale.y * CellSize)));
		rectangle.setPosition(static_cast<float>(obj.transform.pos.x * CellSize), static_cast<float>(obj.transform.pos.y * CellSize));
		Window.draw(rectangle);
	}

	void DrawVertexArray(VertexArray2D& obj)
	{
		sf::VertexArray vertexArray(sf::Quads, obj->size() * 4);
		for (uint64_t index = 0; index < obj->size(); ++index)
		{
			uint64_t i = index * 4;

			vertexArray[i + 0].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::TopLeft>().x, (float)obj[index].GetVerticePosition<Side::TopLeft>().y);
			vertexArray[i + 1].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::TopRight>().x, (float)obj[index].GetVerticePosition<Side::TopRight>().y);
			vertexArray[i + 2].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::BottomRight>().x, (float)obj[index].GetVerticePosition<Side::BottomRight>().y);
			vertexArray[i + 3].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::BottomLeft>().x, (float)obj[index].GetVerticePosition<Side::BottomLeft>().y);

			vertexArray[i + 0].color = sf::Color(obj[index].GetVertice<Side::TopLeft>().color.r, obj[index].GetVertice<Side::TopLeft>().color.g, obj[index].GetVertice<Side::TopLeft>().color.b, obj[index].GetVertice<Side::TopLeft>().color.a);
			vertexArray[i + 1].color = sf::Color(obj[index].GetVertice<Side::TopRight>().color.r, obj[index].GetVertice<Side::TopLeft>().color.g, obj[index].GetVertice<Side::TopLeft>().color.b, obj[index].GetVertice<Side::TopLeft>().color.a);
			vertexArray[i + 2].color = sf::Color(obj[index].GetVertice<Side::BottomRight>().color.r, obj[index].GetVertice<Side::TopLeft>().color.g, obj[index].GetVertice<Side::TopLeft>().color.b, obj[index].GetVertice<Side::TopLeft>().color.a);
			vertexArray[i + 3].color = sf::Color(obj[index].GetVertice<Side::BottomLeft>().color.r, obj[index].GetVertice<Side::TopLeft>().color.g, obj[index].GetVertice<Side::TopLeft>().color.b, obj[index].GetVertice<Side::TopLeft>().color.a);
		}
		Window.draw(vertexArray);
	}
}

void SFMLRender::Init()
{
	Window.create(sf::VideoMode(WindowSize, WindowSize), "SFML works!");
	ensure(&Window);
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
	for (auto& [key, drawable] : Entity->drawables)
	{
		std::visit(overloaded(
			[](FQuad2D obj)
			{
				DrawQuad2D(obj);
			}, 
			[](VertexArray2D obj)
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
