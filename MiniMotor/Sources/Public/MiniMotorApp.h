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
#include "VulkanRender.h"
using CurrentRender = VulkanRender;
#endif

#include "Slate/SlateContainer.h"

class World;

class MM_API MiniMotorApp final
{
public:

	static MiniMotorApp* GetInstance();

	// Initialize the application
	void Init();

	// Run the application
	void Run();

	// Shutdown the application
	void Shutdown();

	void SetWorld(World* world);

	bool OnEvents(const Events& event);

	void PushLayer(SContainer* slate);

	void DrawLine(const FVec2& start, const FVec2& end, const FColor& color);

	void DrawQuad(const FVec2& position, const FVec2& size, const FColor& color);

private:

	MiniMotorApp();

	~MiniMotorApp();

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

	static MiniMotorApp* m_Instance;
};