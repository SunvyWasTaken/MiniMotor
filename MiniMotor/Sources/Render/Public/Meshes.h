#pragma once

#include "Maths.h"

#define NEW_TEXTURE_TYPE(_name) struct _name { constexpr inline decltype(auto) name() const { return #_name; }; };

namespace Sunset
{
	struct Vertex
	{
		FVec3 Position;
		FVec3 Normal;
		FVec2 TexCoords;
	};

	NEW_TEXTURE_TYPE(Diffuse)
	NEW_TEXTURE_TYPE(Specular)

	using TextureType = std::variant<Diffuse, Specular>;

	struct Texture
	{
		Texture() : isValid(false), id(0) {}

		Texture(const uint32_t _id, const TextureType& _type)
			: isValid(true)
			, id(_id)
			, type(_type)
		{
		}

		bool isValid;
		uint32_t id;
		TextureType type;
	};

	using TextureList = std::array<Texture, std::variant_size_v<TextureType>>;

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
