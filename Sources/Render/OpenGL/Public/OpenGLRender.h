#pragma once

#include "BasicRender.h"

class Camera;
class ShaderOGL;

class OpenGLRender : public BasicRender<OpenGLRender>
{
public:
	OpenGLRender();

	virtual ~OpenGLRender();

	void Run(Camera* cam);

	bool IsRunning();

	void LoadVirtualObject();

	void CursorPosCallback(double xPos, double yPos);

private:

	void LoadShader();

	void ProcessInput();

private:

	std::unique_ptr<ShaderOGL> shaderProgram;
	std::unique_ptr<ShaderOGL> lightProgram;

	uint lightVAO;
};
