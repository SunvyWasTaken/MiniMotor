#include "Application.h"

#include "ImGuiLayer.h"
#include "Renderer.h"
#include "Scene.h"
#include "MesheComponent.h"
#include "TransformComponent.h"

#include "VertexArray.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace
{
	Sunset::Camera m_Camera;

	bool b_IsWinOpen = true;

	Sunset::ImGuiLayer* imLayer;
}

namespace Sunset
{
	BasicApp* BasicApp::AppPtr = nullptr;

	BasicApp::BasicApp()
		: m_Window(nullptr)
		, m_Scene(nullptr)
	{
		AppPtr = this;
		LOG("BasicApp init")
		m_Window = std::make_unique<WindowPC>(WindowData{});
		m_Window->SetEventCallBack(std::bind(&BasicApp::OnEvents, AppPtr, std::placeholders::_1));

		m_Scene = std::make_unique<Scene>();

		imLayer = new Sunset::ImGuiLayer();
		PushLayer(imLayer);
	}

	BasicApp::~BasicApp()
	{}

	void BasicApp::Run()
	{
		Init();


		std::shared_ptr<Sunset::ShaderOGL> shader = std::make_shared<Sunset::ShaderOGL>("../../MiniMotor/Sources/Shaders/vShader.vert", "../../MiniMotor/Sources/Shaders/fShader.frag");

		double previousTime = m_Window->GetTime();
		while (b_IsWinOpen)
		{
			double nextTime = m_Window->GetTime();
			float deltatime = nextTime - previousTime;
			previousTime = nextTime;

			Update();
			m_Scene->Update(deltatime);
			m_Camera.Update(deltatime);

			RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1.0});
			RenderCommand::Clear();
			Renderer::BeginScene(m_Camera);

			auto IDs = m_Scene->entitys.view<MeshComponent, TransformComponent>();
			for (auto ID : IDs)
			{
				auto mesh = m_Scene->entitys.get<MeshComponent>(ID);
				auto trans = m_Scene->entitys.get<TransformComponent>(ID);
				Renderer::Submit(shader, mesh(), trans(), mesh.color);
			}
			
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

	void BasicApp::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	Camera* BasicApp::GetCam()
	{
		return &m_Camera;
	}

}