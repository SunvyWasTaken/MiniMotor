#include "Application.h"

#include "ImGuiLayer.h"
#include "Renderer.h"

#include "VertexArray.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

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

		std::array<float, 3*7> Vertices = {
			-.5f, -.5f, 0.f, .8f, .2f, .8f, 1.f,
			 .5f, -.5f, 0.f, .2f, .3f, .8f, 1.f,
			 .0f,  .5f, 0.f, .8f, .8f, .2f, 1.f
		};

		std::array<uint32_t, 3> indices = { 0, 1, 2 };

		LOG("-------------------------------------------")

		std::shared_ptr<VertexArray> VAO = nullptr;
		VAO.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> VBO = nullptr;
		VBO.reset(VertexBuffer::Create(&Vertices[0], Vertices.size()));
		VBO->SetLayout(
			{
				{ShaderDataType::Float3(), "aPos"},
				{ShaderDataType::Float4(), "aColor"}
			});
		VAO->AddVertexBuffer(VBO);

		std::shared_ptr<IndexBuffer> EBO = nullptr;
		EBO.reset(IndexBuffer::Create(&indices[0], indices.size()));

		VAO->SetIndexBuffer(EBO);
		LOG("-------------------------------------------")

		//uint32_t VAO;
		//uint32_t VBO;
		//uint32_t EBO;

		//glCreateVertexArrays(1, &VAO);
		//glGenBuffers(1, &VBO);
		//glGenBuffers(1, &EBO);

		//glBindVertexArray(VAO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);

		//glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), &Vertices[0], GL_STATIC_DRAW);

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);

		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);


		std::shared_ptr<ShaderOGL> shader = std::make_shared<ShaderOGL>("../../MiniMotor/Sources/Shaders/vShader.vert", "../../MiniMotor/Sources/Shaders/fShader.frag");

		while (b_IsWinOpen)
		{
			RenderCommand::SetClearColor({0.8, 0.2, 0.5, 0.1});
			RenderCommand::Clear();
			Renderer::BeginScene(m_Camera);
			Renderer::Submit(shader, VAO);
			//shader->Use();
			//glBindVertexArray(VAO);
			//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

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
		//glDeleteVertexArrays(1, &VAO);
		//glDeleteBuffers(1, &VBO);
		//glDeleteBuffers(1, &EBO);
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