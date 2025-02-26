#pragma once

#include "BasicRender.h"
#include "Lights.h"

struct GLFWwindow;

namespace Sunset
{
	class ShaderOGL;

	class MM_API OpenGLRender : public BasicRender<OpenGLRender>
	{
	public:
		OpenGLRender(GLFWwindow* window);

		virtual ~OpenGLRender() override;

		void SwapBuffers();

		//void BeginFrame();

		//void DrawLight(const Lights* light);

		//void Draw(const Camera* cam, const Mesh* mesh, const Transform& trans);

		//void EndFrame();

	private:

		//void CursorPosCallback(double xPos, double yPos);

		//void LoadShader();

		//void SendInput();

	private:

		//std::unique_ptr<ShaderOGL> shaderProgram;

		//std::array<int, 5> keyPressed;
		//std::array<bool, 5> AvailableIndex;
	};
}

