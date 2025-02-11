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

private:

	void LoadShader();

private:

	std::unique_ptr<ShaderOGL> shaderProgram;
};
