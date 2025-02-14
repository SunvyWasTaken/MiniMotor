#pragma once

#include "Event.h"
#include "Maths.h"

#define RET_CRTP(x, returnType) returnType x() { DerivedPtr tmp = static_cast<DerivedPtr>(this); return tmp->x(); }
#define CRTP(x) RET_CRTP(x, void)


using uint = unsigned int;
using CallbackFunction = std::function<void(const Events&)>;

class GLFWwindow;
class Mesh;

namespace Sunset
{
	class Camera;

	template <typename Derived>
	class BasicRender
	{
		using DerivedPtr = Derived*;
	public:
		BasicRender(const std::string& _name, const FVec2& size)
			: m_WindowTitle(_name.c_str())
			, m_Width(size.x)
			, m_Height(size.y)
		{ }

		virtual ~BasicRender() = default;

		CRTP(BeginFrame)

		void Draw(const Camera* cam, const Mesh* mesh, const Transform& trans)
		{
			DerivedPtr tmp = static_cast<DerivedPtr>(this);
			tmp->Draw(cam, mesh, trans);
		}

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

	protected:

		GLFWwindow* m_Window = nullptr;

		int m_Width = 800;
		int m_Height = 600;

		std::string m_WindowTitle = "LeafEngine";

		CallbackFunction OnEventFunc;
	};
}
