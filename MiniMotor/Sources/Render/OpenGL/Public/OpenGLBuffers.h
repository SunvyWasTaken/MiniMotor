#pragma once

#include "Buffers.h"

namespace Sunset
{
	class VertexOpenGlBuffer : public VertexBuffer
	{
	public:
		VertexOpenGlBuffer(float* vertices, size_t size);
		virtual ~VertexOpenGlBuffer() override;
		virtual void Bind() override;
		virtual void UnBind() override;

	private:
		uint32_t m_RenderID;
	};

	class IndexOpenGlBuffer : public IndexBuffer
	{

	};
}
