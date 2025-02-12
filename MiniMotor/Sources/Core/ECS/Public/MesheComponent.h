#pragma once

#include "Meshes.h"

// Mesh component is only the component for the ECS it will store the mesh which is going to be draw during the draw function.
class MM_API MeshComponent final
{
public:
	explicit MeshComponent(const Mesh& _mesh);

	Mesh* operator()()
	{
		return &mesh;
	}

private:
	Mesh mesh;
};
