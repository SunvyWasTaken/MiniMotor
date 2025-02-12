#include "MiniMotor.h"

using OpenGLApp = BasicApp<OpenGLRender>;

int main()
{
	std::unique_ptr<OpenGLApp> curr = std::make_unique<OpenGLApp>();
	curr->Run();
	return 0;
}
