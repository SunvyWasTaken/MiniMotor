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

class Mesh final
{
public:

	using vertexList = std::vector<Vertex>;
	using indiceList = std::vector<uint32_t>;
	using texturelist = std::vector<Texture>;

	explicit Mesh(vertexList _vertices/*, indiceList _indices, texturelist _textures*/ );

	~Mesh();

	void Draw(class ShaderOGL* shader) const;

public:

	vertexList vertices;

	//indiceList indices;

	//texturelist textures;

private:

	uint32_t VBO, VAO, EBO;
	
};
