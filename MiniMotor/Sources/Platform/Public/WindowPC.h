#pragma once

#include "Window.h"

struct GLFWwindow;

namespace Sunset
{
	class BasicRender;
	class OpenGLRender;
	class VulkanRender;

	class WindowPC : public Window<WindowPC>
	{
		using RenderContext = std::variant<std::unique_ptr<BasicRender>, std::unique_ptr<OpenGLRender>, std::unique_ptr<VulkanRender>>;

	public:

		WindowPC(const WindowData& props);

		virtual ~WindowPC();

		void OnUpdate();

		void SetEventCallBack(const EventCallBackFn& _callback);
		void SetVSync(bool _enable);
		bool IsVSync() const;

		void* GetNativeWindow() const { return m_Window; }

	private:

		// Init the GLFW window and all the needs
		void Init();

		// Init the Context (OpenGL or Vulkan)
		void CreateContext();

	private:

		GLFWwindow* m_Window;

		RenderContext m_Context;

		bool VSync;
	};
}