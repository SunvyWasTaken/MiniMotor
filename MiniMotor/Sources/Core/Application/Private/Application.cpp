#include "Application.h"

#include "ImGuiLayer.h"
#include "Renderer.h"

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
	{
		AppPtr = this;
		LOG("BasicApp init")
		m_Window = std::make_unique<WindowPC>(WindowData{});
		m_Window->SetEventCallBack(std::bind(&BasicApp::OnEvents, AppPtr, std::placeholders::_1));

		imLayer = new Sunset::ImGuiLayer();
		PushLayer(imLayer);
	}

	BasicApp::~BasicApp()
	{}

	void BasicApp::Run()
	{
		Init();

		std::array<float, 9> Vertices = {
			-.5f, -.5f, 0.f,
			 .5f, -.5f, 0.f,
			 .0f,  .5f, 0.f
		};

		std::array<uint32_t, 3> indices = { 0, 1, 2 };

		std::shared_ptr<VertexArray> VAO = nullptr;
		VAO.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> VBO = nullptr;
		VBO.reset(VertexBuffer::Create(&Vertices[0], Vertices.size()));
		VBO->SetLayout(
			{
				{ShaderDataType::Float3(), "aPos"}
			});
		VAO->AddVertexBuffer(VBO);

		std::shared_ptr<IndexBuffer> EBO = nullptr;
		EBO.reset(IndexBuffer::Create(&indices[0], indices.size()));

		VAO->SetIndexBuffer(EBO);

		std::shared_ptr<ShaderOGL> shader = std::make_shared<ShaderOGL>("../../MiniMotor/Sources/Shaders/vShader.vert", "../../MiniMotor/Sources/Shaders/fShader.frag");

		double previousTime = m_Window->GetTime();
		while (b_IsWinOpen)
		{
			double nextTime = m_Window->GetTime();
			float deltatime = previousTime - nextTime;
			previousTime = nextTime;

			m_Camera.Update((float)deltatime);

			RenderCommand::SetClearColor({0.8, 0.2, 0.5, 0.1});
			RenderCommand::Clear();
			Renderer::BeginScene(m_Camera);
			Renderer::Submit(shader, VAO);
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