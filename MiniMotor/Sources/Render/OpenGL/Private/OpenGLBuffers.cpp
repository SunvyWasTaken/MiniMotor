#include "OpenGLBuffers.h"

#include <glad/glad.h>

namespace
{
	template <typename T>
	void CheckVertexBufferData(GLuint bufferID, T* expectedData, size_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		std::vector<T> bufferData(size);
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(T), bufferData.data());

		for (size_t i = 0; i < size; ++i)
		{
			if (bufferData[i] != expectedData[i])
			{
				std::cerr << "VertexBuffer data mismatch at index " << i << ": expected " << expectedData[i] << ", got " << bufferData[i] << std::endl;
				return;
			}
		}
		std::cout << "VertexBuffer data is correct." << std::endl;
	}
}

namespace Sunset
{
	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, size_t size)
		: m_RenderID(0)
	{
		LOG("VBO creation")
		glGenBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
	}

	OpenGlVertexBuffer::~OpenGlVertexBuffer()
	{
		LOG("VBO destruction")
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
		LOG("EBO creation")
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		LOG("EBO destruction")
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		LOG("Bind index")
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

