#pragma once

#include "BasicRender.h"

class OpenGLRender : public BasicRender<OpenGLRender>
{
public:
	OpenGLRender();

	virtual ~OpenGLRender();

	void Run(float deltatime);

	bool IsRunning();
};
