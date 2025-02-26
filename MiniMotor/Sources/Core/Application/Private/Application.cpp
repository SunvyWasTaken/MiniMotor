#include "Application.h"
#include "BasicRender.h"
#include "ImGuiLayer.h"

#include "Renderer.h"

Sunset::BasicApp* Sunset::BasicApp::AppPtr = nullptr;

namespace Sunset
{
	BasicApp::BasicApp()
		: m_Window(nullptr)
		, b_IsWinOpen(true)

	{
		AppPtr = this;

		m_Window = std::make_unique<WindowPC>(WindowData{});
		m_Window->SetEventCallBack(std::bind(&BasicApp::OnEvents, AppPtr, std::placeholders::_1));
	}

	BasicApp::~BasicApp()
	{}

	void BasicApp::Run()
	{
		Init();
		while (b_IsWinOpen)
		{
			RenderCommand::SetClearColor({0.1, 0.1, 0.1, 0.1});
			RenderCommand::Clear();
			Renderer::BeginScene();
			Renderer::EndScene();
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