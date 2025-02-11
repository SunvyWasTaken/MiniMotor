
#include "Camera.h"
#include "Event.h"
#include "OpenGLRender.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	std::array<glm::vec3, 10> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
}

OpenGLRender::OpenGLRender()
	: BasicRender<OpenGLRender>()
	, shaderProgram(nullptr)
	, lightProgram(nullptr)
	, lightVAO(0)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Weigth, m_Height, m_WindowTitle.c_str(), NULL, NULL);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return;
	}

	glViewport(0, 0, m_Weigth, m_Height);
	glEnable(GL_DEPTH_TEST);

	LoadShader();

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			static_cast<OpenGLRender*>(glfwGetWindowUserPointer(window))->CursorPosCallback(xPos, yPos);
		});

	BasicRender<OpenGLRender>::PostInit();
}

OpenGLRender::~OpenGLRender()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

void OpenGLRender::Run(Camera* cam)
{
	ProcessInput();

	glClearColor(0.f, 0.6f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->Use();

	Perspective<FMat4> perspective;
	Radian<float> radian;
	FMat4 projection = perspective(radian(45.f), (float)m_Weigth / (float)m_Height, 0.1f, 100.f);

	shaderProgram->SetMatrice4("view", cam->GetViewMatrice());
	shaderProgram->SetMatrice4("projection", projection);

	shaderProgram->SetVec3F("LightColor", FVec3{1.f, 1.f, 1.f});

	glBindVertexArray(VAO);
	for (uint i = 0; i < cubePositions.size(); ++i)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * (i % 3 == 0 ? i : (float)glfwGetTime());
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shaderProgram->SetMatrice4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	lightProgram->Use();

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	projection = perspective(radian(45.f), (float)m_Weigth / (float)m_Height, 0.1f, 100.f);

	shaderProgram->SetMatrice4("view", cam->GetViewMatrice());
	shaderProgram->SetMatrice4("projection", projection);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	shaderProgram->SetMatrice4("model", model);

	// draw the light cube object
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool OpenGLRender::IsRunning()
{
	return !glfwWindowShouldClose(m_Window);
}

void OpenGLRender::LoadVirtualObject()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Light part
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void OpenGLRender::LoadShader()
{
	shaderProgram = std::make_unique<ShaderOGL>("../../LeafEngine/Sources/Shaders/vShader.vert", "../../LeafEngine/Sources/Shaders/fShader.frag");
	lightProgram = std::make_unique<ShaderOGL>("../../LeafEngine/Sources/Shaders/vLightShader.vert", "../../LeafEngine/Sources/Shaders/fLightShader.frag");
}

void OpenGLRender::ProcessInput()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);

	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Events even = KeyEvent{ GLFW_KEY_W };
		OnEventFunc(even);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Events even = KeyEvent{ GLFW_KEY_S };
		OnEventFunc(even);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Events even = KeyEvent{ GLFW_KEY_A };
		OnEventFunc(even);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Events even = KeyEvent{ GLFW_KEY_D };
		OnEventFunc(even);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		Events even = KeyEvent{ GLFW_KEY_Q };
		OnEventFunc(even);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS)
	{
		Events even = KeyEvent{ GLFW_KEY_E };
		OnEventFunc(even);
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
