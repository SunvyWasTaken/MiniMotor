#pragma once

class GLFWwindow;

using uint = unsigned int;

template <typename Derived>
class BasicRender
{
	using DerivedPtr = Derived*;
public:
	BasicRender() = default;

	virtual ~BasicRender() = default;

	void Run(float deltatime)
	{
		DerivedPtr tmp = static_cast<DerivedPtr>(this);
		tmp->Run(deltatime);
	}

	bool IsRunning()
	{
		DerivedPtr tmp = static_cast<DerivedPtr>(this);
		return tmp->IsRunning();
	}

protected:

	GLFWwindow* m_Window = nullptr;

	int m_Weigth = 800;
	int m_Height = 600;

	std::string m_WindowTitle = "LeafEngine";

	// Vertex buffer object.
	uint VBO;
	// Vertex array Object.
	uint VAO;
};
