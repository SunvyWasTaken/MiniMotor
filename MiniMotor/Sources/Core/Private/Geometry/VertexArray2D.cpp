#include "Geometry/VertexArray2D.h"

VertexArray2D::VertexArray2D()
{
}

VertexArray2D::~VertexArray2D()
{
}

void VertexArray2D::Resize(size_t size)
{
	quads.resize(size);
}

FQuad2D& VertexArray2D::operator[](const size_t index)
{
	return quads[index];
}

Quad2DLists* VertexArray2D::operator->()
{
	return &quads;
}
