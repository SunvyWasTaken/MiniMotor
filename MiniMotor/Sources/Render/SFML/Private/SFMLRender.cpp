// Copyright Shimmer Studios : All rights reserved.

#include "CoreMinimal.h"
#include "Entitys.h"
#include "SFMLRender.h"
#include "Utils/StateMachine.h"
#include "Slate/SlateContainer.h"
#include "Textures/SFMLTextures.h"

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include <iostream>

#define CellSize 100

#define WindowSizeX 850
#define WindowSizeY 850

// This is a private
namespace
{
	sf::RenderWindow Window;

	sf::Font font;

	sf::Clock DeltaClock;

	sf::Clock CurrClock;

	std::chrono::duration<double> GenClock;

	sf::Vector2f OldMousePosition;

	double currZoom = 1.0;

	bool IsMousePressed = false;

	void DrawQuad2D(FQuad2D& obj)
	{
		sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(obj.transform.scale.x * CellSize), static_cast<float>(obj.transform.scale.y * CellSize)));
		rectangle.setPosition(static_cast<float>(obj.transform.pos.x * CellSize), static_cast<float>(obj.transform.pos.y * CellSize));
		Window.draw(rectangle);
	}

	void DrawVertexArray(VertexArray2D& obj)
	{
		sf::Texture* texture = SFMLTextures::GetInstance()->GetTextures(obj.texture.filename);
		IVec2 textureCoord = obj.texture.coord;
		sf::VertexArray vertexArray(sf::Quads, 4);
		vertexArray.resize(obj->size() * 4);
		for (uint64_t index = 0; index < obj->size(); ++index)
		{
			uint64_t i = index * 4;

			vertexArray[i + 0].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::TopLeft>().x, (float)obj[index].GetVerticePosition<Side::TopLeft>().y);
			vertexArray[i + 1].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::TopRight>().x, (float)obj[index].GetVerticePosition<Side::TopRight>().y);
			vertexArray[i + 2].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::BottomRight>().x, (float)obj[index].GetVerticePosition<Side::BottomRight>().y);
			vertexArray[i + 3].position = sf::Vector2f((float)obj[index].GetVerticePosition<Side::BottomLeft>().x, (float)obj[index].GetVerticePosition<Side::BottomLeft>().y);

			vertexArray[i + 0].texCoords = sf::Vector2f((float)textureCoord.x, (float)textureCoord.y);
			vertexArray[i + 1].texCoords = sf::Vector2f((float)textureCoord.x + 1753, (float)textureCoord.y);
			vertexArray[i + 2].texCoords = sf::Vector2f((float)textureCoord.x + 1753, (float)textureCoord.y + 1753);
			vertexArray[i + 3].texCoords = sf::Vector2f((float)textureCoord.x, (float)textureCoord.y + 1753);

			vertexArray[i + 0].color = sf::Color(obj[index].GetVertice<Side::TopLeft>().color.r, obj[index].GetVertice<Side::TopLeft>().color.g, obj[index].GetVertice<Side::TopLeft>().color.b, obj[index].GetVertice<Side::TopLeft>().color.a);
			vertexArray[i + 1].color = sf::Color(obj[index].GetVertice<Side::TopRight>().color.r, obj[index].GetVertice<Side::TopRight>().color.g, obj[index].GetVertice<Side::TopRight>().color.b, obj[index].GetVertice<Side::TopRight>().color.a);
			vertexArray[i + 2].color = sf::Color(obj[index].GetVertice<Side::BottomRight>().color.r, obj[index].GetVertice<Side::BottomRight>().color.g, obj[index].GetVertice<Side::BottomRight>().color.b, obj[index].GetVertice<Side::BottomRight>().color.a);
			vertexArray[i + 3].color = sf::Color(obj[index].GetVertice<Side::BottomLeft>().color.r, obj[index].GetVertice<Side::BottomLeft>().color.g, obj[index].GetVertice<Side::BottomLeft>().color.b, obj[index].GetVertice<Side::BottomLeft>().color.a);
		}
		sf::RenderStates states;
		states.texture = texture;
		Window.draw(vertexArray, states);
	}

	void HandleAnchor(SContainer* slate)
	{
		ImVec2 targetPosition;
		std::visit(overloaded(
			[&](const TopLeft)
			{
				targetPosition = ImVec2{ (float)slate->GetPosition()->x, (float)slate->GetPosition()->y };
			},
			[&](const Left)
			{
				targetPosition = ImVec2{ (float)slate->GetPosition()->x, (float)slate->GetPosition()->y - (float)slate->GetSize()->y / 2 };
			},
			[&](const BottomLeft)
			{
				targetPosition = ImVec2{ (float)slate->GetPosition()->x, (float)slate->GetPosition()->y - (float)slate->GetSize()->y };
			},
			[&](const TopRight)
			{
				targetPosition = ImVec2{ (float)slate->GetPosition()->x - (float)slate->GetSize()->x, (float)slate->GetPosition()->y };
			},
			[&](const Right)
			{
				targetPosition = ImVec2{ (float)slate->GetPosition()->x - (float)slate->GetSize()->x, (float)slate->GetPosition()->y - (float)slate->GetSize()->y / 2 };
			},
			[&](const BottomRight)
			{
				targetPosition = ImVec2{ (float)slate->GetPosition()->x - (float)slate->GetSize()->x, (float)slate->GetPosition()->y - (float)slate->GetSize()->y };
			},
			[&](const Top)
			{
				targetPosition = ImVec2{ (float)slate->GetPosition()->x - (float)slate->GetSize()->x / 2, (float)slate->GetPosition()->y };
			},
			[&](const Bottom)
			{
				targetPosition = ImVec2{ (float)slate->GetPosition()->x - (float)slate->GetSize()->x / 2, (float)slate->GetPosition()->y - (float)slate->GetSize()->y };
			},
			[&](const Center)
			{
				targetPosition = ImVec2{ (float)slate->GetPosition()->x - (float)slate->GetSize()->x / 2, (float)slate->GetPosition()->y - (float)slate->GetSize()->y / 2 };
			}
		), slate->GetPadding());
		ImGui::SetWindowPos(targetPosition);
	}

	void DrawChild(SContainer* slate)
	{
		for (auto& child : slate->m_Children)
		{
			if (SButton* obj = dynamic_cast<SButton*>(child))
			{
				if(ImGui::Button(obj->m_Text.c_str()))
				{
					auto start = std::chrono::high_resolution_clock::now();
					obj->OnPressed();
					auto end = std::chrono::high_resolution_clock::now();
					GenClock = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
				}
				ImGui::SameLine();
				ImGui::Text("Time elapsed : %f s", GenClock.count());
			}
			else if (SEditableText* obj = dynamic_cast<SEditableText*>(child))
			{
				ImGui::InputInt(obj->m_Text.c_str(), &obj->value);
				ImGui::SameLine();
				if(ImGui::Button("Send"))
				{
					obj->OnPressed(IVec2{obj->value, obj->value});
				}
			}
		}
	}

}

void SFMLRender::Init()
{
	Window.create(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);
	ensure(&Window);
	Window.setFramerateLimit(0);
	Window.setVerticalSyncEnabled(false);
	bool loaded = font.loadFromFile("Ressources/PoiretOne-Regular.ttf");
	ensure(loaded);
	ImGui::SFML::Init(Window);
}

void SFMLRender::Update()
{
	ImGui::SFML::Update(Window, CurrClock.restart());
}

void SFMLRender::Draw()
{
	ImGui::Begin("Performance", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);
	ImGui::SetWindowSize(ImVec2{ 200, 50 });
	ImGui::SetWindowPos(ImVec2{ 0, 0 });
	ImGui::Text("Framerate : %f", 1.f / DeltaClock.getElapsedTime().asSeconds());
	DeltaClock.restart();
	ImGui::End();
	ImGui::SFML::Render(Window);
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

void SFMLRender::HandleEvents()
{
	sf::Event currEvent;
	while (Window.pollEvent(currEvent))
	{
		if (currEvent.type == sf::Event::Closed)
		{
			if(EventCall(MEvents::OnWindowClose()))
				return;
		}
		else if (currEvent.type == sf::Event::Resized)
		{
			float ratio = (float)currEvent.size.width / (float)currEvent.size.height;
			sf::View view = Window.getView();
			view.setSize(WindowSizeY * ratio, WindowSizeX);
			Window.setView(view);
			return;
		}
		else if (currEvent.type == sf::Event::KeyPressed)
		{
			if (currEvent.key.code >= 0 && currEvent.key.code <= 25)
			{
				if(EventCall(MEvents::OnKeyPressed(currEvent.key.code + 65)))
					return;
			}
		}
		else if (currEvent.type == sf::Event::KeyReleased)
		{
			if (currEvent.key.code >= 0 && currEvent.key.code <= 25)
			{
				if(EventCall(MEvents::OnKeyReleased(currEvent.key.code + 65)))
					return;
			}
		}
		else if (currEvent.type == sf::Event::MouseButtonPressed)
		{
			if(EventCall(MEvents::OnMouseButtonPressed(currEvent.key.code)))
				return;

			if (currEvent.mouseButton.button == sf::Mouse::Right)
			{
				OldMousePosition = sf::Vector2f{ (float)currEvent.mouseButton.x, (float)currEvent.mouseButton.y };
				IsMousePressed = true;
			}
		}
		else if (currEvent.type == sf::Event::MouseButtonReleased)
		{
			if(EventCall(MEvents::OnMouseButtonReleased(currEvent.key.code)))
				return;

			if (currEvent.mouseButton.button == sf::Mouse::Right)
			{
				IsMousePressed = false;
			}
		}
		else if (currEvent.type == sf::Event::MouseMoved)
		{
			if(EventCall(MEvents::OnMouseMoved({ currEvent.mouseMove.x, currEvent.mouseMove.y})))
				return;

			if (IsMousePressed)
			{
				sf::View view = Window.getView();
				sf::Vector2f diff = sf::Vector2f{(float)currEvent.mouseMove.x, (float)currEvent.mouseMove.y} - OldMousePosition;
				view.move(diff.x*-(currZoom), diff.y*-(currZoom));
				OldMousePosition = sf::Vector2f{ (float)currEvent.mouseMove.x, (float)currEvent.mouseMove.y };
				Window.setView(view);
			}
		}
		else if (currEvent.type == sf::Event::MouseWheelScrolled)
		{
			if (EventCall(MEvents::OnMouseScrolled(currEvent.mouseWheelScroll.delta)))
				return;

			sf::View view = Window.getView();
			if (currEvent.mouseWheelScroll.delta > 0)
			{
				if (currZoom > 0.15)
				{
					view.zoom(0.95);
					currZoom -= 0.05;
				}
			}
			else
			{
				if (currZoom < 2.0)
				{
					view.zoom(1.05);
					currZoom += 0.05;
				}
			}
			if (currZoom == 0)
			{
				view.setSize(sf::VideoMode::getDesktopMode().height, sf::VideoMode::getDesktopMode().width);
			}
			Window.setView(view);
		}
		ImGui::SFML::ProcessEvent(currEvent);
	}
}

void SFMLRender::ClearWindow()
{
	Window.clear();
}

void SFMLRender::CloseWindow()
{
	Window.close();
	ImGui::SFML::Shutdown();
}

void SFMLRender::DrawSlate(SContainer* slate)
{
	ImGui::Begin("Slate", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	HandleAnchor(slate);
	ImGui::SetWindowSize(ImVec2{(float)slate->GetSize()->x, (float)slate->GetSize()->y});

	DrawChild(slate);

	ImGui::End();
}
