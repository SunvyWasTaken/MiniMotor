
#include "OpenGLRender.h"

#include "Camera.h"
#include "Event.h"
#include "Meshes.h"
#include "OpenGLShader.h"
#include "Typelists.h"

#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define NBR_POINT_LIGHT 4

namespace
{
	// Maybe this could be ptr?
	Sunset::Directional directionalLight;
	std::array<Sunset::Point, NBR_POINT_LIGHT> pointLight;

	constexpr std::string_view pointLightName = "pointLight";
}

namespace Sunset
{
	OpenGLRender::OpenGLRender(const std::string& _name, const FVec2 _size)
		: BasicRender<OpenGLRender>(_name, _size)
		, shaderProgram(nullptr)
		, keyPressed({ 0, 0, 0, 0, 0 })
		, AvailableIndex({ true, true, true, true, true })
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowTitle.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSwapInterval(1);

		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_FALSE);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			glfwTerminate();
			return;
		}

		glViewport(0, 0, m_Width, m_Height);
		glEnable(GL_DEPTH_TEST);

		LoadShader();

		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double xPos, double yPos)
			{
				static_cast<OpenGLRender*>(glfwGetWindowUserPointer(window))->CursorPosCallback(xPos, yPos);
			});
		glfwSetFramebufferSizeCallback(m_Window,
			[](GLFWwindow* window, int width, int height)
			{
				static_cast<BasicRender<OpenGLRender>*>(glfwGetWindowUserPointer(window))->OnWindowResize(width, height);
				glViewport(0, 0, width, height);
			});
			// todo : make a InputPolling sys cuz this is ugly
		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				OpenGLRender* winPtr = static_cast<OpenGLRender*>(glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS)
				{
					for (uint8_t i = 0; i < 5; ++i)
					{
						if (winPtr->AvailableIndex[i])
						{
							winPtr->AvailableIndex[i] = false;
							winPtr->keyPressed[i] = key;
							return;
						}
					}
				}
				else if (action == GLFW_RELEASE)
				{
					for (uint8_t i = 0; i < 5; ++i)
					{
						if (winPtr->keyPressed[i] == key)
						{
							winPtr->keyPressed[i] = 0;
							winPtr->AvailableIndex[i] = true;
							return;
						}
					}
				}
			});
	}

	OpenGLRender::~OpenGLRender()
	{
		glfwDestroyWindow(m_Window); // attention a bien destroy la window
		glfwTerminate();
	}

	void OpenGLRender::BeginFrame()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
	}

	void OpenGLRender::DrawLight(const Lights* light)
	{
		std::visit(Overloaded{
		[&](Directional light)
		{
			directionalLight = light;
		},
		[&](Point light)
		{
			for (auto& curr : pointLight)
			{
				if (!curr.isValid)
				{
					curr = light;
					curr.isValid = true;
				}
			}
		},
		[&](SpotLight light)
		{
		}
		}, *light);
	}

	void OpenGLRender::Draw(const Camera* cam, const Mesh* mesh, const Transform& trans)
	{
		SendInput();

		shaderProgram->Use();

		float ambiant = 0.2f;
		float diffuse = 1.f;
		float specular = 0.5f;

		shaderProgram->SetMatrice4("projection", cam->GetProjection());
		shaderProgram->SetMatrice4("view", cam->GetViewMatrice());
		shaderProgram->SetVec3F("viewPos", cam->m_Position);

		shaderProgram->SetVec3F("dirLight.direction", directionalLight.direction);
		shaderProgram->SetVec3F("dirLight.ambient", directionalLight.ambient);
		shaderProgram->SetVec3F("dirLight.diffuse", directionalLight.diffuse);
		shaderProgram->SetVec3F("dirLight.specular", directionalLight.specular);

		size_t i = 0;
		for (auto& curr : pointLight)
		{
			if (!curr.isValid)
			{
				// Break cuz we r (almost sure) there will no more light valid after the first invalid one.
				break;
			}

			std::string name = std::string(pointLightName) + '[' + std::to_string(i) + ']';
			std::string constant = name + ".constant";
			shaderProgram->Set1F(constant.data(), curr.constant);

			++i;
		}

		shaderProgram->Set1F("material.shininess", 1.f);

		// todo : It's should be something like that.
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, trans.position);
		model = glm::scale(model, trans.size);
		// todo : not correct i think i don't know i did cuz i want to rotation for later.
		model = glm::rotate(model, glm::radians(trans.rotation.yaw), glm::vec3(1.f, 0.f, 0.f));
		model = glm::rotate(model, glm::radians(trans.rotation.pitch), glm::vec3{0.f, 1.f, 0.f});
		model = glm::rotate(model, glm::radians(trans.rotation.roll), glm::vec3{0.f, 0.f, 1.f});
		shaderProgram->SetMatrice4("model", model);
		mesh->Draw(shaderProgram.get());
	}

	void OpenGLRender::EndFrame()
	{
		glfwSwapBuffers(m_Window);
	}

	bool OpenGLRender::IsRunning()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void OpenGLRender::CloseWindow()
	{
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
	}

	void OpenGLRender::LoadShader()
	{
		shaderProgram = std::make_unique<ShaderOGL>("../../MiniMotor/Sources/Shaders/vShader.vert", "../../MiniMotor/Sources/Shaders/fShader.frag");
	}

	void OpenGLRender::SendInput()
	{
		for (auto key : keyPressed)
		{
			if (key != 0)
			{
				Events even = KeyEvent{ key };
				OnEventFunc(even);
			}
		}
	}

	void OpenGLRender::CursorPosCallback(double xPos, double yPos)
	{
		Events even = MouseEvent{ (float)xPos, (float)yPos };
		if (OnEventFunc)
		{
			OnEventFunc(even);
		}
	}
}
