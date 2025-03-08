
#include "MesheComponent.h"

#include "Buffers.h"
#include "VertexArray.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

namespace
{

	std::array<float, 12> Vertices = {
		-.1f, -.1f, 0.f,
		 .1f, -.1f, 0.f,
		 .1f,  .1f, 0.f,
		-.1f,  .1f, 0.f
	};

	std::array<uint32_t, 6> indices = { 0, 1, 2, 3, 2, 0 };

	// This function only support JPG and PNG
	// Might cuz issue with image with less or more channel than 3 and 4.
	uint32_t LoadTexture(const std::string& path)
	{
		uint32_t texture;
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 0x1904 + nrChannels, width, height, 0, 0x1904 + nrChannels, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
		return texture;
	}

	template <size_t ...Is>
	void InitTextures(Sunset::TextureList& texture, const Sunset::NamesList& names, std::index_sequence<Is...>)
	{
		((texture[Is] = Sunset::Texture(LoadTexture(names[Is]), typename std::variant_alternative_t<Is, Sunset::TextureType>())),...);
	}
}

namespace Sunset
{
	MeshComponent::MeshComponent(const NamesList& names)
		: color(glm::vec3(1.f))
		, VAO(nullptr)
		, VBO(nullptr)
		, EBO(nullptr)
	{
		//InitTextures(m_Textures, names, std::make_index_sequence<std::variant_size_v<TextureType>>{});
	
		VAO.reset(Sunset::VertexArray::Create());

		std::shared_ptr<Sunset::VertexBuffer> VBO = nullptr;
		VBO.reset(Sunset::VertexBuffer::Create(&Vertices[0], Vertices.size()));
		VBO->SetLayout(
			{
				{Sunset::ShaderDataType::Float3(), "aPos"}
			});
		VAO->AddVertexBuffer(VBO);

		std::shared_ptr<Sunset::IndexBuffer> EBO = nullptr;
		EBO.reset(Sunset::IndexBuffer::Create(&indices[0], indices.size()));

		VAO->SetIndexBuffer(EBO);
	}

	MeshComponent::~MeshComponent()
	{
		for (uint8_t i = 0; i < m_Textures.size(); ++i)
		{
			glDeleteTextures(1, &(m_Textures[i].id));
		}
	}

	std::shared_ptr<VertexArray>& MeshComponent::operator()()
	{
		return VAO;
	}

	TextureList& MeshComponent::GetTextures()
	{
		return m_Textures;
	}
}

