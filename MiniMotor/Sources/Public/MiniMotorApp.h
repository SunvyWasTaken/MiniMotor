
#pragma once

#define RENDERTYPE 1 // 0 = Console, 1 = SFML

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

	void OnEvents(const Events& event);

private:
	
	bool m_IsRunning;

	World* m_World;

	std::unique_ptr<GenericRender<CurrentRender>> m_Render;
};