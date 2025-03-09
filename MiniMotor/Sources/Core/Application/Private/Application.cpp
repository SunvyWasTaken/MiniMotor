#include "Application.h"

#include "ImGuiLayer.h"
#include "Renderer.h"
#include "Scene.h"
#include "MesheComponent.h"
#include "TransformComponent.h"

#include "Inputs.h"
#include "VertexArray.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace
{
	Sunset::Camera m_Camera;

	bool b_IsWinOpen = true;

	Sunset::ImGuiLayer* imLayer;

	std::vector<glm::vec2> points;
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

		// vertex array of the points
		uint32_t VAO;
		uint32_t VBO;

		glLineWidth(5.f);

		double previousTime = m_Window->GetTime();
		while (b_IsWinOpen)
		{
			double nextTime = m_Window->GetTime();
			deltatime = nextTime - previousTime;
			previousTime = nextTime;

			Update();
			m_Scene->Update(deltatime);
			m_Camera.Update(deltatime);

			if (Inputs::IsMouseButtonPressed(0))
			{
				if (VAO) glDeleteVertexArrays(1, &VAO);
				if (VBO) glDeleteBuffers(1, &VBO);

				auto mousPos = Inputs::GetMousePosition();
				mousPos.x = (2.f * mousPos.x / GetWindow().GetWidth()) - 1.f;
				mousPos.y = 1.f - (2.f * mousPos.y / GetWindow().GetHeight());

				glm::vec4 ray_clip(mousPos.x, mousPos.y, -1.0f, 1.0f);

				glm::vec4 ray_eye = glm::inverse(m_Camera.GetProjection()) * ray_clip;
				ray_eye.z = -1.0f;
				ray_eye.w = 0.0f;

				glm::vec3 ray_world = glm::vec3(glm::inverse(m_Camera.GetViewMatrice()) * ray_eye);
				ray_world = glm::normalize(ray_world);

				points.push_back({ ray_world.x, ray_world.y });

				glCreateVertexArrays(1, &VAO);
				glCreateBuffers(1, &VBO);

				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec2), points.data(), GL_DYNAMIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

				glBindVertexArray(0);
			}
			else
			{
				points.clear();
				glDeleteVertexArrays(1, &VAO);
				glDeleteBuffers(1, &VBO);
			}

			LOG("VAO: {}, VBO: {}, points : {}", VAO, VBO, points.size());

			RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1.0});
			RenderCommand::Clear();
			Renderer::BeginScene(m_Camera);

			shader->Use();
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_STRIP, 0, points.size());
			shader->UnBind();

			//auto IDs = m_Scene->entitys.view<MeshComponent, TransformComponent>();
			//for (auto ID : IDs)
			//{
			//	auto mesh = m_Scene->entitys.get<MeshComponent>(ID);
			//	auto trans = m_Scene->entitys.get<TransformComponent>(ID);
			//	Renderer::Submit(shader, mesh(), trans(), mesh.color);
			//}
			
			Renderer::EndScene();

			//for (auto& layer : layerStack)
			//{
			//	layer->OnUpdate();
			//}

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