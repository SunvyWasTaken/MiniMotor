#pragma once

#include "Meshes.h"

class ShaderOGL;
class aiNode;
class aiMesh;
class aiScene;
class aiMaterial;
enum aiTextureType;

// Mesh component is only the component for the ECS it will store the mesh which is going to be draw during the draw function.
class MM_API MeshComponent final
{
public:
	explicit MeshComponent(const std::string& path);

	void Draw(ShaderOGL* shader) const;

	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

private:
	std::vector<Mesh> meshes;

	std::string directory;
};
