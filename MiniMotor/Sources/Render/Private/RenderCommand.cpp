#include "RenderCommand.h"

#include "OpenGLRenderApi.h"

namespace Sunset
{
	RendererApi* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
