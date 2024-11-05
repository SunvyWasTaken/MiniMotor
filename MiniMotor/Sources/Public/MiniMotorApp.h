// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "GenRender.h"

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

	bool OnEvents(const Events& event);

	template <typename WorldType, typename ...Args>
	WorldType* OpenWorld(Args&&... args)
	{
		static_assert(std::is_base_of<World, WorldType>(), "WorldType must derive from World");

		m_World.reset(new WorldType(std::forward<Args>(args)...));
		return m_World.get();
	}

private:

	MiniMotorApp();

	~MiniMotorApp();

	void MainLoop();

	bool IsRunning() const;

private:
	
	bool m_IsRunning;

	std::unique_ptr<World> m_World;

	std::unique_ptr<GenericRender<CurrentRender>> m_Render;

	static MiniMotorApp* m_Instance;
};
