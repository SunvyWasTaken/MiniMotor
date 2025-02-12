#pragma once

#include "Event.h"

#define RET_CRTP(x, returnType) returnType x() { DerivedPtr tmp = static_cast<DerivedPtr>(this); return tmp->x(); }
#define CRTP(x) RET_CRTP(x, void)


class GLFWwindow;
class Camera;
class Mesh;

using uint = unsigned int;
using CallbackFunction = std::function<void(const Events&)>;

template <typename Derived>
class MM_API BasicRender
{
	using DerivedPtr = Derived*;
public:
	BasicRender() = default;

	virtual ~BasicRender() = default;

	CRTP(BeginFrame)

	void Draw(const Camera* cam, const Mesh* mesh)
	{
		DerivedPtr tmp = static_cast<DerivedPtr>(this);
		tmp->Draw(cam, mesh);
	}

	CRTP(EndFrame)

	RET_CRTP(IsRunning, bool)

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

	// Vertex buffer object.
	uint VBO = 0;
	// Vertex array Object.
	uint VAO = 0;

	CallbackFunction OnEventFunc;
};
