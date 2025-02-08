
#include "OpenGLRender.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

OpenGLRender::OpenGLRender()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Weigth, m_Height, m_WindowTitle, NULL, NULL);
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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Swap the image.
	glfwSwapBuffers(m_Window);
	// Get The events
	glfwPollEvents();
}

bool OpenGLRender::IsRunning()
{
	return !glfwWindowShouldClose(m_Window);
}
