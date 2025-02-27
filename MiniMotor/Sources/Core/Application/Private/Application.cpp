#include "Application.h"

#include "ImGuiLayer.h"
#include "Renderer.h"

#include "VertexArray.h"
#include "OpenGLShader.h"

Sunset::BasicApp* Sunset::BasicApp::AppPtr = nullptr;

namespace Sunset
{
	BasicApp::BasicApp()
		: m_Window(nullptr)
		, b_IsWinOpen(true)
	{
		AppPtr = this;
		LOG("BasicApp init")
		m_Window = std::make_unique<WindowPC>(WindowData{});
		m_Window->SetEventCallBack(std::bind(&BasicApp::OnEvents, AppPtr, std::placeholders::_1));
	}

	BasicApp::~BasicApp()
	{}

	void BasicApp::Run()
	{
		Init();

		std::shared_ptr<VertexArray> VAO = nullptr;
		VAO.reset(VertexArray::Create());

		float Vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<VertexBuffer> vbo = nullptr;
		vbo.reset(VertexBuffer::Create(Vertices, sizeof(Vertices)));
		vbo->SetLayout({
			{ ShaderDataType::Float3(), "a_Position"},
			{ ShaderDataType::Float4(), "a_Color"}
		});
		VAO->AddVertexBuffer(vbo);

		std::shared_ptr<IndexBuffer> ebo = nullptr;

		ebo.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		VAO->SetIndexBuffer(ebo);

		std::shared_ptr<ShaderOGL> shader = std::make_shared<ShaderOGL>("../../MiniMotor/Sources/Shaders/vShader.vert", "../../MiniMotor/Sources/Shaders/fShader.frag");

		while (b_IsWinOpen)
		{
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

}