#include "VertexArray.h"

#include "OpenGLVertexArray.h"

namespace Sunset
{
	VertexArray::~VertexArray()
	{
	}

	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}
}