#include "Buffers.h"

#include "OpenGLBuffers.h"

namespace
{
	uint32_t ShaderDataTypeSize(const Sunset::ShaderDataType::Type& type)
	{
		return std::visit(Overloaded
			{
				[](Sunset::ShaderDataType::Float arg)	->uint32_t	{ return sizeof(float); },
				[](Sunset::ShaderDataType::Float2 arg)	->uint32_t	{ return 2 * sizeof(float); },
				[](Sunset::ShaderDataType::Float3 arg)	->uint32_t	{ return 3 * sizeof(float); },
				[](Sunset::ShaderDataType::Float4 arg)	->uint32_t	{ return 4 * sizeof(float); },
				[](Sunset::ShaderDataType::Mat3 arg)	->uint32_t	{ return 4 * 3 * 3; },
				[](Sunset::ShaderDataType::Mat4 arg)	->uint32_t	{ return 4 * 4 * 4; },
				[](Sunset::ShaderDataType::Int arg)		->uint32_t	{ return sizeof(int); },
				[](Sunset::ShaderDataType::Int2 arg)	->uint32_t	{ return 2 * sizeof(int); },
				[](Sunset::ShaderDataType::Int3 arg)	->uint32_t	{ return 3 * sizeof(int); },
				[](Sunset::ShaderDataType::Int4 arg)	->uint32_t	{ return 4 * sizeof(int); },
				[](Sunset::ShaderDataType::Bool arg)	->uint32_t	{ return sizeof(bool); }
			}, type);
	}
}

namespace Sunset
{
	BufferElement::BufferElement(ShaderDataType::Type type /*= ShaderDataType::Bool()*/, const std::string& name /*= ""*/, bool normalized /*= false*/)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
	{

	}

	uint32_t BufferElement::GetComponentCount() const
	{
		return std::visit(Overloaded
			{
				[](ShaderDataType::Float arg)	{ return 1; },
				[](ShaderDataType::Float2 arg)	{ return 2; },
				[](ShaderDataType::Float3 arg)	{ return 3; },
				[](ShaderDataType::Float4 arg)	{ return 4; },
				[](ShaderDataType::Mat3 arg)	{ return 3 * 3; },
				[](ShaderDataType::Mat4 arg)	{ return 4 * 4; },
				[](ShaderDataType::Int arg)		{ return 1; },
				[](ShaderDataType::Int2 arg)	{ return 2; },
				[](ShaderDataType::Int3 arg)	{ return 3; },
				[](ShaderDataType::Int4 arg)	{ return 4; },
				[](ShaderDataType::Bool arg)	{ return 1; }
			}, Type);
	}

	BufferLayout::BufferLayout()
		: m_Stride(0)
	{
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	VertexBuffer::~VertexBuffer()
	{

	}

	VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
	{
		return new OpenGlVertexBuffer(vertices, size);
	}

	IndexBuffer::~IndexBuffer()
	{

	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, size_t count)
	{
		return new OpenGLIndexBuffer(indices, count);
	}

}

