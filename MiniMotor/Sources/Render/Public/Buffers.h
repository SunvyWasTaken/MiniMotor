#pragma once

namespace Sunset
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer();
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		static VertexBuffer* Create(float* vertices, size_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer();
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		static IndexBuffer* Create(uint32_t* indices, size_t size);
	};
}
