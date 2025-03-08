#pragma once

#include "Textures.h"

namespace Sunset
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	
	using NamesList = std::array<std::string, std::variant_size_v<TextureType>>;

	class MM_API MeshComponent final
	{
	public:

		explicit MeshComponent(const NamesList& names);

		~MeshComponent();

		std::shared_ptr<VertexArray>& operator()();

		TextureList& GetTextures();

	public:

		glm::vec3 color;

	private:

		std::shared_ptr<VertexArray> VAO;
		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> EBO;

		TextureList m_Textures;
	};
}
