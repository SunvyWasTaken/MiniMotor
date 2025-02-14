#pragma once

#include "BasicRender.h"

class Camera;
class ShaderOGL;

namespace Sunset
{
	class MM_API OpenGLRender : public BasicRender<OpenGLRender>
	{
	public:
		OpenGLRender(const std::string& _name, const FVec2 _size);

		virtual ~OpenGLRender();

		void BeginFrame();

		void Draw(const Camera* cam, const Mesh* mesh, const Transform& trans);

		void EndFrame();

		bool IsRunning();

		void CloseWindow();

	private:

		void CursorPosCallback(double xPos, double yPos);

		void LoadShader();

		void ProcessInput();

	private:

		std::unique_ptr<ShaderOGL> shaderProgram;
		std::unique_ptr<ShaderOGL> lightProgram;

		std::array<int, 5> keyPressed;
		std::array<bool, 5> AvailableIndex;
	};
}

