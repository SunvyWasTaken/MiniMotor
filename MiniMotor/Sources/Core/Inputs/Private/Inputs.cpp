#include "Inputs.h"

#include "Application.h"

#include <GLFW/glfw3.h>

namespace Sunset
{
	bool Inputs::IsKeyPressed(int32_t key)
	{
		if (void* WinPtr = BasicApp::Get().GetWindow())
		{
			return glfwGetKey(static_cast<GLFWwindow*>(WinPtr), key);
		}
		return false;
	}

}
