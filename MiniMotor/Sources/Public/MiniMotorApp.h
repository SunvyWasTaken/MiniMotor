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

	void SetWorld(World* world);

	bool OnEvents(const Events& event);

	void PushLayer(SContainer* slate);

private:

	MiniMotorApp();

	~MiniMotorApp();

	void MainLoop();

	bool IsRunning() const;

private:
	
	bool m_IsRunning;

	World* m_World;

	SlateContainer m_SlateContainer;

	std::unique_ptr<GenericRender<CurrentRender>> m_Render;

	static MiniMotorApp* m_Instance;
};