#pragma once

#include "Event.h"
#include "Maths.h"
#include "Lights.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>

#include <functional>

#define RET_CRTP(x, returnType) returnType x() { DerivedPtr tmp = static_cast<DerivedPtr>(this); return tmp->x(); }
#define VAR_RET_CRTP(x, returnType) template <typename ...Args> returnType x(Args&&... args) { DerivedPtr tmp = static_cast<DerivedPtr>(this); return tmp->x(std::forward<Args>(args)...); }

#define CRTP(x) RET_CRTP(x, void)
#define CRTP_VAR(x) VAR_RET_CRTP(x, void)

class GLFWwindow;

namespace Sunset
{
	using CallbackFunction = std::function<void(const Events&)>;

	class Camera;
	class Mesh;

	template <typename Derived>
	class BasicRender
	{
		using DerivedPtr = Derived*;
	public:
		BasicRender(const std::string& _name, const FVec2& size)
			: m_Window(nullptr)
			, m_WindowTitle(_name.c_str())
			, m_Width(size.x)
			, m_Height(size.y)
		{ }

		virtual ~BasicRender() = default;

		CRTP(BeginFrame)

		// Will draw light like once. cuz I don't know yet how i want it to be.
		CRTP_VAR(DrawLight)

		CRTP_VAR(Draw)

		CRTP(EndFrame)

		RET_CRTP(IsRunning, bool)

		CRTP(CloseWindow)

		void BindInputCallback(const CallbackFunction& func)
		{
			OnEventFunc = func;
		}

		void OnWindowResize(int width, int height)
		{
			m_Width = width;
			m_Height = height;
		}

		void* GetWindow() const { return m_Window; }

	protected:

		GLFWwindow* m_Window;

		int m_Width;
		int m_Height;

		std::string m_WindowTitle;

		CallbackFunction OnEventFunc;
	};
}
