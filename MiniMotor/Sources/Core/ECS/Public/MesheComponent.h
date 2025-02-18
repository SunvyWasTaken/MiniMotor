#pragma once

#include "Textures.h"

namespace Sunset
{
	class Mesh;

	using NamesList = std::array<std::string, std::variant_size_v<TextureType>>;

	// Mesh component is only the component for the ECS it will store the mesh which is going to be draw during the draw function.
	class MM_API MeshComponent final
	{
	public:

		explicit MeshComponent(const NamesList& names);

		~MeshComponent();

		Mesh* operator()();

	private:

		std::unique_ptr<Mesh> m_Mesh;

		TextureList m_Textures;
	};
}
