#pragma once

#include "BasicRender.h"

namespace Sunset
{
	class ShaderOGL;

	class MM_API OpenGLRender : public BasicRender<OpenGLRender>
	{
	public:
		OpenGLRender(const std::string& _name, const FVec2 _size);

		virtual ~OpenGLRender() override;

		void BeginFrame();

		void DrawLight(const Lights* light);

		void Draw(const Camera* cam, const Mesh* mesh, const Transform& trans);

		void EndFrame();

		bool IsRunning();

		void CloseWindow();

	private:

		void CursorPosCallback(double xPos, double yPos);

		void LoadShader();

		void SendInput();

	private:

		std::unique_ptr<ShaderOGL> shaderProgram;

		std::array<int, 5> keyPressed;
		std::array<bool, 5> AvailableIndex;
	};
}

