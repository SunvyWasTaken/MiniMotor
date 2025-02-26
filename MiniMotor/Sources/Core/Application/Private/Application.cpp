#include "Application.h"
#include "BasicRender.h"
#include "Camera.h"
#include "Entity.h"
#include "ImGuiLayer.h"
#include "InputComponent.h"
#include "MesheComponent.h"
#include "Meshes.h"
#include "OpenGLRender.h"
#include "TransformComponent.h"

Sunset::BasicApp* Sunset::BasicApp::AppPtr = nullptr;

namespace Sunset
{
	BasicApp::BasicApp()
		: m_Window(nullptr)
		, b_IsWinOpen(true)
	{
		AppPtr = this;

		m_Window = std::make_unique<WindowPC>(WindowData{}, OpenGL());
		m_Window->SetEventCallBack(std::bind(&BasicApp::OnEvents, this, std::placeholders::_1));

		imLayer = new ImGuiLayer();
		PushLayer(imLayer);
		
	}

	BasicApp::~BasicApp()
	{
	}

	void BasicApp::Run()
	{
		Init();

		while (b_IsWinOpen)
		{
			for (auto& layer : layerStack)
			{
				layer->OnUpdate();
			}

			imLayer->Begin();
			for (auto& layer : layerStack)
			{
				layer->OnImGuiRender();
			}
			imLayer->End();

			m_Window->OnUpdate();
		}
	}

	void BasicApp::OnEvents(const Events& even)
	{
		std::visit(Overloaded
		{
			[&](KeyEvent arg)
			{
			},
			[&](MouseEvent arg)
			{
			},
			[&](WinCloseEvent arg)
			{
				b_IsWinOpen = false;
			}
		}, even);
	}

}