#include "OpenGLBuffers.h"

#include <glad/glad.h>

namespace Sunset
{
	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, size_t size)
		: m_RenderID(0)
	{
		LOG("Bind vertex buffer : {}", size);
		glCreateBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
	}

	OpenGlVertexBuffer::~OpenGlVertexBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}
	
	void OpenGlVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}
	
	void OpenGlVertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/************************************************************************/
	/* Index Buffer															*/
	/************************************************************************/

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, size_t count)
		: m_Count(count)
	{
		LOG("Bind Index buffer");
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

