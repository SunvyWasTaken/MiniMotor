#pragma once

#include "OpenGLRender.h"
#include "Application.h"

using OpenGLApp = BasicApp<OpenGLRender>;

template <typename T>
void RunApp()
{
	std::unique_ptr<T> curr = std::make_unique<T>();
	curr->Run();
}

