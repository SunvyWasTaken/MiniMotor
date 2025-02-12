#pragma once

#include "Maths.h"

struct Vertex
{
	FVec3 Position;
	FVec3 Normal;
	FVec2 TexCoords;
};

#define NEW_TEXTURE_TYPE(_name) struct _name { constexpr inline std::string_view name() const { return #_name; }; };

namespace TTexture
{
	NEW_TEXTURE_TYPE(Diffuse)
	NEW_TEXTURE_TYPE(Specular)

	using TextureType = std::variant<Diffuse, Specular>;
}

struct Texture
{
	uint32_t id;
	TTexture::TextureType type;
};

class MM_EXPORT Mesh final
{
public:

	using vertexList = std::vector<Vertex>;
	using indicesList = std::vector<uint32_t>;

	Mesh(vertexList _vertices, indicesList _indices);

	~Mesh();

	void Draw(class ShaderOGL* shader) const;

public:

	vertexList vertices;
	indicesList indices;

private:

	uint32_t VBO, VAO, EBO;

};
