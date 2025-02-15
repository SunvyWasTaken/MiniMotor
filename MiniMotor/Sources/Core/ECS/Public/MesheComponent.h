#pragma once

#include "Meshes.h"

namespace Sunset
{
	class Mesh;

	// Mesh component is only the component for the ECS it will store the mesh which is going to be draw during the draw function.
	class MM_API MeshComponent final
	{
	public:

		MeshComponent();

		~MeshComponent();

		Mesh* operator()();

	private:
		std::unique_ptr<Mesh> mesh;

		Texture BaseColor;
		Texture SpecColor;

	};
}
