// Copyright Shimmer Studios : All rights reserved.

#pragma once

#define RENDERTYPE 2 // 0 = Console, 1 = SFML

#if RENDERTYPE == 0
#include "ConsoleRender.h"
using CurrentRender = ConsoleRender;
#elif RENDERTYPE == 1
#include "SFMLRender.h"
using CurrentRender = SFMLRender;
#elif RENDERTYPE == 2
#include "OpenGLRender.h"
using CurrentRender = OpenGLRender;
#endif

#include "Slate/SlateContainer.h"

class World;

class MM_API MiniMotorApp
{
public:
	MiniMotorApp();
	~MiniMotorApp();

	// Initialize the application
	void Init();

	// Run the application
	void Run();

	// Shutdown the application
	void Shutdown();

	void SetWorld(World* world);

	bool OnEvents(const Events& event);

	void PushLayer(SContainer* slate);

private:

	// Send event through all slates

	template <typename eventType>
	bool SendEventThroughSlate(const eventType& event)
	{
		for (auto& slate : m_SlateContainer)
		{
			if (slate->OnEvent(event))
			{
				return true;
			}
		}
		return false;
	}

	void MainLoop();

	bool IsRunning() const;

private:
	
	bool m_IsRunning;

	World* m_World;

	SlateContainer m_SlateContainer;

	std::unique_ptr<GenericRender<CurrentRender>> m_Render;
};