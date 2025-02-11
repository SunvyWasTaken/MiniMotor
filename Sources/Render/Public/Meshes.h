#pragma once

#include "Maths.h"

struct Vertex
{
	FVec3 Position;
	FVec3 Normal;
	FVec2 TexCoords;
};

struct Texture
{
	using uint = unsigned int;
	uint id;
	std::string type;
};

class Mesh
{
	using uint = unsigned int;
	using vertexList = std::vector<Vertex>;
	using indiceList = std::vector<uint>;
	using texturelist = std::vector<Texture>;

public:

	Mesh(vertexList _vertices, indiceList _indices, texturelist _textures);

	void Draw(class ShaderOGL* shader);

public:

	vertexList vertices;

	indiceList indices;

	texturelist textures;

private:

	uint VBO, VAO, EBO;

	void setupMesh();
	
};
