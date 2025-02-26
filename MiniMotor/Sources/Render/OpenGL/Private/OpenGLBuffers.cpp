#include "OpenGLBuffers.h"

#include <glad/glad.h>

namespace Sunset
{
	VertexOpenGlBuffer::VertexOpenGlBuffer(float* vertices, size_t size)
		: m_RenderID(0)
	{
		glCreateBuffers(1, &m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexOpenGlBuffer::~VertexOpenGlBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}
	
	void VertexOpenGlBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}
	
	void VertexOpenGlBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

