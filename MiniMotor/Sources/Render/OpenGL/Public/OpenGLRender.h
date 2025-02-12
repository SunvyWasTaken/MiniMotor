#pragma once

#include "BasicRender.h"

class Camera;
class ShaderOGL;

class MM_API OpenGLRender : public BasicRender<OpenGLRender>
{
public:
	OpenGLRender();

	virtual ~OpenGLRender();

	void BeginFrame();

	void Draw(const Camera* cam, const MeshComponent* mesh);

	void EndFrame();

	bool IsRunning();

private:

	void CursorPosCallback(double xPos, double yPos);

	void LoadShader();

	void ProcessInput();

private:

	std::unique_ptr<ShaderOGL> shaderProgram;
	std::unique_ptr<ShaderOGL> lightProgram;

	uint lightVAO;
};
