// Copyright Shimmer Studios : All rights reserved.

#include "OpenGLRender.h"

#include "Entitys.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

namespace
{
	GLFWwindow* m_windowOpenGL(nullptr);
	const int m_width = 800;
	const int m_height = 600;
	const std::string m_title = "OpenGL Render";

	void DrawQuad(FQuad2D quad)
	{
		//glBegin(GL_QUADS);
		//glColor4f(quad.color.r, quad.color.g, quad.color.b, quad.color.a);
		//glVertex2f(quad.vertices[0].position.x, quad.vertices[0].position.y);
		//glVertex2f(quad.vertices[1].position.x, quad.vertices[1].position.y);
		//glVertex2f(quad.vertices[2].position.x, quad.vertices[2].position.y);
		//glVertex2f(quad.vertices[3].position.x, quad.vertices[3].position.y);
		//glEnd();
	}

	void DrawVertexArray(const VertexArray2D& obj)
	{
		//glBegin(GL_QUADS);
		//for (auto& quad : *obj)
		//{
		//	glColor4f(quad.color.r, quad.color.g, quad.color.b, quad.color.a);
		//	glVertex2f(quad.vertices[0].position.x, quad.vertices[0].position.y);
		//	glVertex2f(quad.vertices[1].position.x, quad.vertices[1].position.y);
		//	glVertex2f(quad.vertices[2].position.x, quad.vertices[2].position.y);
		//	glVertex2f(quad.vertices[3].position.x, quad.vertices[3].position.y);
		//}
		//glEnd();
	}
}

void OpenGLRender::Init()
{	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_windowOpenGL = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	if (!m_windowOpenGL)
	{
		std::cout << "Failed to create GLFW window 1" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_windowOpenGL);

	//Load glad so it configures OpenGL
	gladLoadGL();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glViewport(0, 0, m_width, m_height);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_windowOpenGL, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void OpenGLRender::Update()
{
}

void OpenGLRender::HandleEvents()
{
	//Create new imgui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	glfwPollEvents();
}

void OpenGLRender::Draw()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool OpenGLRender::IsWindowOpen()
{
	return !glfwWindowShouldClose(m_windowOpenGL);;
}

void OpenGLRender::BufferFrame(Entity* Entity)
{
	for (auto& [key, drawable] : Entity->drawables)
	{
		std::visit(overloaded(
		[](FQuad2D obj)
		{
			/*DrawQuad(obj);*/
		},
		[](VertexArray2D obj)
		{
			DrawVertexArray(obj);
		}), drawable);
	}
}

void OpenGLRender::ClearWindow()
{
	//Clear background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//Clear the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui::EndFrame();
}

void OpenGLRender::CloseWindow()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_windowOpenGL);
	glfwTerminate();
}

void OpenGLRender::DrawSlate(SContainer* slate)
{
}
