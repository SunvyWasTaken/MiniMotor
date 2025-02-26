#pragma once

#include "Window.h"

struct GLFWwindow;

namespace Sunset
{
	struct OpenGL{};
	struct Vulkan{};

	using RenderType = std::variant<OpenGL, Vulkan>;

	template <typename T>
	class BasicRender;
	class OpenGLRender;
	class VulkanRender;

	class WindowPC : public Window<WindowPC>
	{
		using RenderContext = std::variant<BasicRender<OpenGLRender>, BasicRender<VulkanRender>>;

	public:

		WindowPC(const WindowData& props, const RenderType& context);

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

	public:
		
		RenderType ContextType;

	private:

		GLFWwindow* m_Window;

		std::unique_ptr<RenderContext> m_Context;

		EventCallBackFn EventCallBack;

		bool VSync;
	};
}