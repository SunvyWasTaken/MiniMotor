// Copyright Shimmer Studios : All rights reserved.

#include "MiniMotorApp.h"
#include "World.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

MiniMotorApp::MiniMotorApp()
	: m_IsRunning(true)
	, m_World(nullptr)
	, m_Render(std::make_unique<CurrentRender>())
{
	m_Render->Init();
	m_Render->BindEvents(std::bind(&MiniMotorApp::OnEvents, this, std::placeholders::_1));
}

MiniMotorApp::~MiniMotorApp()
{
}

void MiniMotorApp::Init()
{
}

void MiniMotorApp::Run()
{
	while (IsRunning())
	{
		MainLoop();
	}
}

void MiniMotorApp::Shutdown()
{
	m_Render->CloseWindow();
	delete m_Instance;
}

void MiniMotorApp::SetWorld(World* world)
{
	ensure(world);
	m_World = world;
}

bool MiniMotorApp::OnEvents(const Events& event)
{
	return event.Visit(
		[&](const MEvents::OnWindowClose& tmp)->bool
		{
			m_IsRunning = false;
			return true;
		},
		[&](const MEvents::OnWindowResize& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnWindowFocus& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnWindowLostFocus& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnWindowMoved& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnAppTick& tmp)->bool
		{
			m_World->Update(tmp.m_deltatime);
			return true;
		},
		[&](const MEvents::OnAppUpdate& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnAppRender& tmp)->bool
		{
			m_World->DrawEntitys();
			return true;
		},
		[&](const MEvents::OnKeyPressed& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnKeyReleased& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnMouseButtonPressed& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnMouseButtonReleased& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnMouseMoved& tmp)->bool
		{
			return false;
		},
		[&](const MEvents::OnMouseScrolled& tmp)->bool
		{
			return false;
		});
}

void MiniMotorApp::PushLayer(SContainer* slate)
{
	m_SlateContainer.PushLayer(slate);
}

MiniMotorApp* MiniMotorApp::GetInstance()
{
	if (!m_Instance)
	{
		m_Instance = new MiniMotorApp();
	}
	return m_Instance;
}

void MiniMotorApp::MainLoop()
{
	m_Render->Update();
}

bool MiniMotorApp::IsRunning() const
{
	return m_IsRunning && m_Render->IsWindowOpen();
}

MiniMotorApp* MiniMotorApp::m_Instance = nullptr;
