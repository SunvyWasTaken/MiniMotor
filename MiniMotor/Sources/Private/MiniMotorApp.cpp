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
	m_Render->EventCall.Bind(this, &MiniMotorApp::OnEvents);
}

MiniMotorApp::~MiniMotorApp()
{
}

void MiniMotorApp::Init()
{
}

void MiniMotorApp::Run()
{
	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(MainLoop, 60, 1);
	#endif
	while (IsRunning())
	{
		MainLoop();
	}
}

void MiniMotorApp::Shutdown()
{
	m_Render->CloseWindow();
}

void MiniMotorApp::SetWorld(World* world)
{
	ensure(world);
	m_World = world;
}

bool MiniMotorApp::OnEvents(const Events& event)
{
	return std::visit(overloaded(
		[this](const MEvents::OnWindowClose tmp)->bool
		{
			m_IsRunning = false;
			return true;
		},
		[this](const MEvents::OnWindowResize tmp)->bool
		{
			return false;
		},
		[this](const MEvents::OnWindowFocus tmp)->bool
		{
			return false;
		},
		[this](const MEvents::OnWindowLostFocus tmp)->bool
		{
			return false;
		},
		[this](const MEvents::OnWindowMoved tmp)->bool
		{
			return false;
		},
		[this](const MEvents::OnAppTick tmp)->bool
		{
			return false;
		},
		[this](const MEvents::OnAppUpdate tmp)->bool
		{
			return false;
		},
		[this](const MEvents::OnAppRender tmp)->bool
		{
			return false;
		},
		[this](const MEvents::OnKeyPressed tmp)->bool
		{
			return SendEventThroughSlate(tmp);
		},
		[this](const MEvents::OnKeyReleased tmp)->bool
		{
			return SendEventThroughSlate(tmp);
		},
		[this](const MEvents::OnMouseButtonPressed tmp)->bool
		{
			return SendEventThroughSlate(tmp);
		},
		[this](const MEvents::OnMouseButtonReleased tmp)->bool
		{
			return SendEventThroughSlate(tmp);
		},
		[this](const MEvents::OnMouseMoved tmp)->bool
		{
			return SendEventThroughSlate(tmp);
		},
		[this](const MEvents::OnMouseScrolled tmp)->bool
		{
			return SendEventThroughSlate(tmp);
		}
	), event);
}

void MiniMotorApp::PushLayer(SContainer* slate)
{
	m_SlateContainer.PushLayer(slate);
}

void MiniMotorApp::MainLoop()
{
	m_Render->Update();
	m_Render->HandleEvents();
	m_World->Update();
	for (auto& slate : m_SlateContainer)
	{
		m_Render->DrawSlate(slate);
	}
	m_World->BufferFrameEntitys(*m_Render);
	m_Render->Draw();
	m_Render->ClearWindow();
}

bool MiniMotorApp::IsRunning() const
{
	return m_IsRunning && m_Render->IsWindowOpen();
}
