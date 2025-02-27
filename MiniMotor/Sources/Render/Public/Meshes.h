#pragma once

#include "Textures.h"

namespace Sunset
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
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
