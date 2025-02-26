#include "WindowPC.h"

#include "BasicRender.h"
#include "OpenGLRender.h"
#include "VulkanRender.h"

#include "RendererApi.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace
{
	bool s_GLFMInitialized = false;

	void OnWindowClose(GLFWwindow* window)
	{
		Sunset::WindowData& data = *(static_cast<Sunset::WindowData*>(glfwGetWindowUserPointer(window)));
		Sunset::Events even = Sunset::WinCloseEvent();
		data.EventCallBack(even);
	}
}

namespace Sunset
{
	WindowPC::WindowPC(const WindowData& props)
		: Window(props)
		, m_Window(nullptr)
		, VSync(true)
	{
		LOG("Window creation")
		Init();
		CreateContext();
	}

	WindowPC::~WindowPC()
	{
		LOG("WinPc destroyed");
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowPC::OnUpdate()
	{
		glfwPollEvents();
		std::visit([this](auto&& arg)
		{
			arg->SwapBuffers();
		}, m_Context);
	}

	void WindowPC::SetEventCallBack(const EventCallBackFn& _callback)
	{
		m_Data.EventCallBack = _callback;
	}

	void WindowPC::SetVSync(bool _enable)
	{
		glfwSwapInterval(static_cast<int>(_enable));
		VSync = _enable;
	}

	bool WindowPC::IsVSync() const
	{
		return VSync;
	}

	void WindowPC::Init()
	{
		if (!s_GLFMInitialized)
		{
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			// glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFMInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			glfwTerminate();
			LOG("Load Glad failed!");
			return;
		}
		LOG("Load Glad succed")

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(VSync);

		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);

		glfwSetWindowCloseCallback(m_Window, &OnWindowClose);

		//glfwSetCursorPosCallback(m_Window,
		//	[](GLFWwindow* window, double xPos, double yPos)
		//	{
		//		static_cast<OpenGLRender*>(glfwGetWindowUserPointer(window))->CursorPosCallback(xPos, yPos);
		//	});
		//glfwSetFramebufferSizeCallback(m_Window,
		//	[](GLFWwindow* window, int width, int height)
		//	{
		//		static_cast<BasicRender<OpenGLRender>*>(glfwGetWindowUserPointer(window))->OnWindowResize(width, height);
		//		glViewport(0, 0, width, height);
		//	});
		//// todo : make a InputPolling sys cuz this is ugly
		//glfwSetKeyCallback(m_Window,
		//	[](GLFWwindow* window, int key, int scancode, int action, int mods)
		//	{
		//		OpenGLRender* winPtr = static_cast<OpenGLRender*>(glfwGetWindowUserPointer(window));
		//		if (action == GLFW_PRESS)
		//		{
		//			for (uint8_t i = 0; i < 5; ++i)
		//			{
		//				if (winPtr->AvailableIndex[i])
		//				{
		//					winPtr->AvailableIndex[i] = false;
		//					winPtr->keyPressed[i] = key;
		//					return;
		//				}
		//			}
		//		}
		//		else if (action == GLFW_RELEASE)
		//		{
		//			for (uint8_t i = 0; i < 5; ++i)
		//			{
		//				if (winPtr->keyPressed[i] == key)
		//				{
		//					winPtr->keyPressed[i] = 0;
		//					winPtr->AvailableIndex[i] = true;
		//					return;
		//				}
		//			}
		//		}
		//	});
	}

	void WindowPC::CreateContext()
	{
		LOG("Create Contex");
		std::visit(Overloaded
		{
			[&](Render::None arg)
			{

			},
			[&](Render::OpenGL arg)
			{
				m_Context = std::make_unique<OpenGLRender>(m_Window);
			},
			[&](Render::Vulkan arg)
			{
				
			}
		}, RendererApi::GetAPI());
	}
}