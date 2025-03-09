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

	bool Inputs::IsMouseButtonPressed(int32_t button)
	{
		BasicApp& app = BasicApp::Get();
		return glfwGetMouseButton((GLFWwindow*)app.GetWindow().GetNativeWindow(), button) == GLFW_PRESS;
	}

	glm::vec2 Inputs::GetMousePosition()
	{
		double x, y;
		BasicApp& app = BasicApp::Get();
		glfwGetCursorPos((GLFWwindow*)app.GetWindow().GetNativeWindow(), &x, &y);

		auto height = app.GetWindow().GetHeight();
		auto width = app.GetWindow().GetWidth();

		if (x < 0)
			x = 0;
		else if (x > width)
			x = width;

		if (y < 0)
			y = 0;
		else if(y > height)
			y = height;

		return glm::vec2(x, y);
	}

}
