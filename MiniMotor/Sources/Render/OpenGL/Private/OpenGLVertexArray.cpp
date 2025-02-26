#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace
{
	GLenum ShaderDataTypeToOpenGLBaseType(const Sunset::ShaderDataType::Type& type)
	{
		return std::visit(Overloaded
		{
			[](Sunset::ShaderDataType::Float arg)	{ return GL_FLOAT; },
			[](Sunset::ShaderDataType::Float2 arg)	{ return GL_FLOAT; },
			[](Sunset::ShaderDataType::Float3 arg)	{ return GL_FLOAT; },
			[](Sunset::ShaderDataType::Float4 arg)	{ return GL_FLOAT; },
			[](Sunset::ShaderDataType::Mat3 arg)	{ return GL_FLOAT; },
			[](Sunset::ShaderDataType::Mat4 arg)	{ return GL_FLOAT; },
			[](Sunset::ShaderDataType::Int arg)		{ return GL_INT; },
			[](Sunset::ShaderDataType::Int2 arg)	{ return GL_INT; },
			[](Sunset::ShaderDataType::Int3 arg)	{ return GL_INT; },
			[](Sunset::ShaderDataType::Int4 arg)	{ return GL_INT; },
			[](Sunset::ShaderDataType::Bool arg)	{ return GL_BOOL; }
		}, type);
	}
}

namespace Sunset
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (uint32_t index = 0; const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				static_cast<const void*>(&element.Offset));
			++index;
		}
		m_VertexBuffers.emplace_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}