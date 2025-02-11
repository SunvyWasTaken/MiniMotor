#pragma once

class GLFWwindow;
class Camera;
class Event;

using uint = unsigned int;
using CallbackFunction = std::function<void(Event)>;

template <typename Derived>
class BasicRender
{
	using DerivedPtr = Derived*;
public:
	BasicRender() = default;

	virtual ~BasicRender() = default;

	void Run(Camera* cam)
	{
		DerivedPtr tmp = static_cast<DerivedPtr>(this);
		tmp->Run(cam);
	}

	bool IsRunning()
	{
		DerivedPtr tmp = static_cast<DerivedPtr>(this);
		return tmp->IsRunning();
	}

	void BindInputCallback(const CallbackFunction& func)
	{
		DerivedPtr tmp = static_cast<DerivedPtr>(this);
		tmp->BindInputCallback(std::forward<CallbackFunction>(func));
	}

protected:

	void PostInit()
	{
		LoadVirtualObject();
	}
	
private:

	void LoadVirtualObject()
	{
		DerivedPtr tmp = static_cast<DerivedPtr>(this);
		tmp->LoadVirtualObject();
	}	

protected:

	GLFWwindow* m_Window = nullptr;

	int m_Weigth = 800;
	int m_Height = 600;

	std::string m_WindowTitle = "LeafEngine";

	// Vertex buffer object.
	uint VBO = 0;
	// Vertex array Object.
	uint VAO = 0;
};
