#include "VertexArray.h"

#include "OpenGLVertexArray.h"
#include "RendererApi.h"

namespace Sunset
{
	VertexArray::~VertexArray()
	{
		LOG("Vertex array destruction")
	}

	VertexArray* VertexArray::Create()
	{
		return std::visit(Overloaded
		{
			[&](Render::None arg)	->VertexArray*	{ return nullptr; },
			[&](Render::OpenGL arg)	->VertexArray*	{ return new OpenGLVertexArray(); },
			[&](Render::Vulkan arg)	->VertexArray*	{ return nullptr; }
		}, RendererApi::GetAPI());
	}
}