
#include "OpenGLRender.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
	ShaderOGL* shaderProgram = nullptr;

	void LoadShader()
	{
		
	}
}

OpenGLRender::OpenGLRender()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Weigth, m_Height, m_WindowTitle.c_str(), NULL, NULL);
	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return;
	}

	glViewport(0, 0, m_Weigth, m_Height);
	glEnable(GL_DEPTH_TEST);
}

OpenGLRender::~OpenGLRender()
{
	glfwTerminate();
}

void OpenGLRender::Run(float deltatime)
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool OpenGLRender::IsRunning()
{
	return !glfwWindowShouldClose(m_Window);
}
