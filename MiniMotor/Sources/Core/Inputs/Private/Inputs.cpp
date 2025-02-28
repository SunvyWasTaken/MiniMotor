#include "Inputs.h"

#include "Application.h"

#include <GLFW/glfw3.h>

namespace Sunset
{
	bool Inputs::IsKeyPressed(int32_t key)
	{
		BasicApp& app = BasicApp::Get();
		return glfwGetKey((GLFWwindow*)app.GetWindow().GetNativeWindow(), key) == GLFW_PRESS;
	}

	bool Inputs::IsKeyReleased(int32_t key)
	{
		BasicApp& app = BasicApp::Get();
		return glfwGetKey((GLFWwindow*)app.GetWindow().GetNativeWindow(), key) == GLFW_RELEASE;
	}

}
