

#include "MiniMotorApp.h"
#include "World.h"

MiniMotorApp::MiniMotorApp()
	: m_IsRunning(true)
	, m_World(nullptr)
	, m_Render(std::unique_ptr<CurrentRender>())
{
}

MiniMotorApp::~MiniMotorApp()
{
}

void MiniMotorApp::Init()
{
	m_Render->Init();
	m_Render->EventCall.Bind(std::bind(&MiniMotorApp::OnEvents, this, std::placeholders::_1));
}

void MiniMotorApp::Run()
{
	while (m_IsRunning)
	{
		m_Render->HandleEvents();
		m_World->BufferFrameEntitys(*m_Render);
		m_Render->Draw();
		m_Render->ClearWindow();
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

void MiniMotorApp::OnEvents(const Events& event)
{
	//std::visit(overloaded(
	//	[this](const MEvents::OnClose tmp) { m_IsRunning = false; },
	//	[this](const MEvents::OnResize tmp) {  },
	//	[this](const MEvents::OnFocus tmp) {  },
	//	[this](const MEvents::OnLostFocus tmp) {  },
	//	[this](const MEvents::OnMoved tmp) {  },
	//	[this](const MEvents::OnAppTick tmp) {  },
	//	[this](const MEvents::OnAppUpdate tmp) {  },
	//	[this](const MEvents::OnAppRender tmp) {  },
	//	[this](const MEvents::OnKeyPressed tmp) {  },
	//	[this](const MEvents::OnKeyReleased tmp) {  },
	//	[this](const MEvents::OnMouseButtonPressed tmp) {  },
	//	[this](const MEvents::OnMouseButtonReleased tmp) {  },
	//	[this](const MEvents::OnMouseMoved tmp) {  },
	//	[this](const MEvents::OnMouseScrolled tmp) {  }
	//	), event);
}
