#pragma once

#include "Event.h"
#include "Maths.h"

struct GLFWwindow;

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
		BasicRender(GLFWwindow* m_Window)
			: m_Window(m_Window)
		{ }

		virtual ~BasicRender() = default;

		CRTP(SwapBuffers)

		//CRTP(BeginFrame)

		//// Will draw light like once. cuz I don't know yet how i want it to be.
		//CRTP_VAR(DrawLight)

		//CRTP_VAR(Draw)

		//CRTP(EndFrame)

		//RET_CRTP(IsRunning, bool)

	protected:
		
		GLFWwindow* m_Window;

	};
}
