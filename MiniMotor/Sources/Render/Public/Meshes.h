#pragma once

#include "Maths.h"
#include "Textures.h"

namespace Sunset
{
	struct Vertex
	{
		FVec3 Position;
		FVec3 Normal;
		FVec2 TexCoords;
	};

	class MM_EXPORT Mesh final
	{
	public:

		using VertexList = std::vector<Vertex>;

		explicit Mesh(const VertexList& _vertices, const TextureList& _textures);

		~Mesh();

		void Draw(class ShaderOGL* shader) const;

	public:

		VertexList Vertices;
		TextureList Textures;

	private:

		uint32_t VBO, VAO;

	};
}
