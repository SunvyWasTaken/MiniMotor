
#include "CoreMinimal.h"
#include "Entitys.h"
#include "SFMLRender.h"
#include "Utils/StateMachine.h"

#include <SFML/Graphics.hpp>

#define CellSize 100

#define WindowSizeX 850
#define WindowSizeY 850

// This is a private
namespace
{
	sf::RenderWindow Window;

	sf::Font font;

	sf::Clock CurrClock;

	void DrawQuad2D(FQuad2D& obj)
	{
		sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(obj.transform.scale.x * CellSize), static_cast<float>(obj.transform.scale.y * CellSize)));
		rectangle.setPosition(static_cast<float>(obj.transform.pos.x * CellSize), static_cast<float>(obj.transform.pos.y * CellSize));
		Window.draw(rectangle);
	}

	void DrawVertexArray(VertexArray2D& obj)
	{
		sf::VertexArray vertexArray(sf::Quads, 4);
		vertexArray.resize(obj->size() * 4);
		for (uint64_t index = 0; index < obj->size(); ++index)
		{
			uint64_t i = index * 4;

			vertexArray[i + 0].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::TopLeft>().x, (float)obj[index].GetVerticePosition<Side::TopLeft>().y);
			vertexArray[i + 1].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::TopRight>().x, (float)obj[index].GetVerticePosition<Side::TopRight>().y);
			vertexArray[i + 2].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::BottomRight>().x, (float)obj[index].GetVerticePosition<Side::BottomRight>().y);
			vertexArray[i + 3].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::BottomLeft>().x, (float)obj[index].GetVerticePosition<Side::BottomLeft>().y);

			vertexArray[i + 0].color = sf::Color(obj[index].GetVertice<Side::TopLeft>().color.r, obj[index].GetVertice<Side::TopLeft>().color.g, obj[index].GetVertice<Side::TopLeft>().color.b, obj[index].GetVertice<Side::TopLeft>().color.a);
			vertexArray[i + 1].color = sf::Color(obj[index].GetVertice<Side::TopRight>().color.r, obj[index].GetVertice<Side::TopRight>().color.g, obj[index].GetVertice<Side::TopRight>().color.b, obj[index].GetVertice<Side::TopRight>().color.a);
			vertexArray[i + 2].color = sf::Color(obj[index].GetVertice<Side::BottomRight>().color.r, obj[index].GetVertice<Side::BottomRight>().color.g, obj[index].GetVertice<Side::BottomRight>().color.b, obj[index].GetVertice<Side::BottomRight>().color.a);
			vertexArray[i + 3].color = sf::Color(obj[index].GetVertice<Side::BottomLeft>().color.r, obj[index].GetVertice<Side::BottomLeft>().color.g, obj[index].GetVertice<Side::BottomLeft>().color.b, obj[index].GetVertice<Side::BottomLeft>().color.a);
		}
		Window.draw(vertexArray);
	}
}

void SFMLRender::Init()
{
	Window.create(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);
	ensure(&Window);
	bool loaded = font.loadFromFile("Ressources/PoiretOne-Regular.ttf");
	ensure(loaded);
}

void SFMLRender::HandleEvents()
{
	sf::Event event;
	while (Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			EventCall(MEvents::OnClose());
		}
		else if(event.type == sf::Event::Resized)
		{
			float ratio = (float)event.size.width / (float)event.size.height;
			sf::View view = Window.getView();
			view.setSize(WindowSizeY * ratio, WindowSizeX);
			Window.setView(view);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			EventCall(MEvents::OnKeyPressed());
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			EventCall(MEvents::OnKeyReleased());
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			EventCall(MEvents::OnMouseButtonPressed());
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			EventCall(MEvents::OnMouseButtonReleased());
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			EventCall(MEvents::OnMouseMoved());
		}
		else if (event.type == sf::Event::MouseWheelScrolled)
		{
			EventCall(MEvents::OnMouseScrolled());
		}
	}
}

void SFMLRender::Draw()
{
	sf::Time curr = CurrClock.restart();
	sf::Text text;
	text.setFont(font);
	text.setString("FPS : " + std::to_string(1.f / curr.asSeconds()));
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	Window.draw(text);
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
