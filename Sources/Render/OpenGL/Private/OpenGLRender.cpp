
#include "Camera.h"
#include "Event.h"
#include "OpenGLRender.h"
#include "OpenGLShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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

	unsigned int texBaseColor;
	unsigned int texSpec;

	void LoadTexture(unsigned int& texture, const std::string& path)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 0x1904 + nrChannels, width, height, 0, 0x1904 + nrChannels, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
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
	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			static_cast<OpenGLRender*>(glfwGetWindowUserPointer(window))->CursorPosCallback(xPos, yPos);
		});
	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
			static_cast<BasicRender<OpenGLRender>*>(glfwGetWindowUserPointer(window))->OnWindowResize(width, height);
			glViewport(0, 0, width, height);
		});

	BasicRender<OpenGLRender>::PostInit();

	LoadTexture(texBaseColor, "../../Ressources/SunsetBaseColor.jpg");
	LoadTexture(texSpec, "../../Ressources/SunsetSpec.png");
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
	FMat4 projection = perspective(radian(45.f), (float)m_Width / (float)m_Height, 0.1f, 100.f);
	shaderProgram->SetMatrice4("view", cam->GetViewMatrice());
	shaderProgram->SetMatrice4("projection", projection);

	shaderProgram->SetVec3F("light.direction", { -0.2f, -1.0f, -0.3f });
	shaderProgram->SetVec3F("viewPos", cam->m_Position);

	// light properties
	shaderProgram->SetVec3F("light.ambient", {0.2f, 0.2f, 0.2f});
	shaderProgram->SetVec3F("material.diffuse", {0.0f, 0.0f, 0.0f});
	shaderProgram->SetVec3F("light.diffuse", {0.5f, 0.5f, 0.5f});
	shaderProgram->SetVec3F("light.specular", {1.0f, 1.0f, 1.0f});

	// material properties
	shaderProgram->Set1F("material.shininess", 64.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texBaseColor);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texSpec);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Light part
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
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
