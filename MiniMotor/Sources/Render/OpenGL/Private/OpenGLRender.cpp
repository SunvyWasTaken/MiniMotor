
#include "Camera.h"
#include "Event.h"
#include "Meshes.h"
#include "OpenGLRender.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

OpenGLRender::OpenGLRender(const std::string& _name, const FVec2 _size)
	: BasicRender<OpenGLRender>(_name, _size)
	, shaderProgram(nullptr)
	, lightProgram(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowTitle.c_str(), NULL, NULL);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return;
	}

	glViewport(0, 0, m_Width, m_Height);
	glEnable(GL_DEPTH_TEST);

	LoadShader();

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
	glfwSetKeyCallback(m_Window, 
	[](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (OpenGLRender* OGLWin = static_cast<OpenGLRender*>(glfwGetWindowUserPointer(window)))
		{
			Events ev = KeyEvent{ key };
			OGLWin->OnEventFunc(ev);
		}
	});
}

OpenGLRender::~OpenGLRender()
{
	glfwTerminate();
}

void OpenGLRender::BeginFrame()
{
	glClearColor(0.f, 0.6f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRender::Draw(const Camera* cam, const Mesh* mesh)
{
	shaderProgram->Use();

	Perspective<FMat4> perspective;
	Radian<float> radian;
	FMat4 projection = perspective(radian(45.f), (float)m_Width / (float)m_Height, 0.1f, 100.f);
	shaderProgram->SetMatrice4("view", cam->GetViewMatrice());
	shaderProgram->SetMatrice4("projection", projection);

	shaderProgram->SetVec3F("light.direction", { -0.2f, -1.0f, -0.3f });
	shaderProgram->SetVec3F("viewPos", cam->m_Position);

	// light properties
	shaderProgram->SetVec3F("light.ambient", { 0.2f, 0.2f, 0.2f });
	shaderProgram->SetVec3F("light.diffuse", { 0.5f, 0.5f, 0.5f });
	shaderProgram->SetVec3F("light.specular", { 1.0f, 1.0f, 1.0f });

	// todo : It's should be something like that.
	glm::mat4 model = glm::mat4(1.0f);
	shaderProgram->SetMatrice4("model", model);
	mesh->Draw(shaderProgram.get());
}

void OpenGLRender::EndFrame()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
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
	lightProgram = std::make_unique<ShaderOGL>("../../MiniMotor/Sources/Shaders/vLightShader.vert", "../../MiniMotor/Sources/Shaders/fLightShader.frag");
}

void OpenGLRender::CursorPosCallback(double xPos, double yPos)
{
	Events even = MouseEvent{ (float)xPos, (float)yPos };
	if (OnEventFunc)
	{
		OnEventFunc(even);
	}
}
