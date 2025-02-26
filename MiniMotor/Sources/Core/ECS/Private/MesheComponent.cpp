
#include "MesheComponent.h"
#include "Meshes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

namespace
{
	// Todo : this should be temporary
	std::vector<Sunset::Vertex> vertices = {
		// positions						// normals					// texture coords
		Sunset::Vertex{glm::vec3{-1.f, -1.f, -1.f},  glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{0.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{ 1.f, -1.f, -1.f},  glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{1.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{ 1.f,  1.f, -1.f},  glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{1.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{ 1.f,  1.f, -1.f},  glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{1.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{-1.f,  1.f, -1.f},  glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{0.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{-1.f, -1.f, -1.f},  glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{0.0f, 0.0f}},

		Sunset::Vertex{glm::vec3{-1.f, -1.f,  1.f},  glm::vec3{0.0f,  0.0f, 1.0f},   glm::vec2{0.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{ 1.f, -1.f,  1.f},  glm::vec3{0.0f,  0.0f, 1.0f},   glm::vec2{1.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{ 1.f,  1.f,  1.f},  glm::vec3{0.0f,  0.0f, 1.0f},   glm::vec2{1.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{ 1.f,  1.f,  1.f},  glm::vec3{0.0f,  0.0f, 1.0f},   glm::vec2{1.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{-1.f,  1.f,  1.f},  glm::vec3{0.0f,  0.0f, 1.0f},   glm::vec2{0.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{-1.f, -1.f,  1.f},  glm::vec3{0.0f,  0.0f, 1.0f},   glm::vec2{0.0f, 0.0f}},

		Sunset::Vertex{glm::vec3{-1.f,  1.f,  1.f}, glm::vec3{-1.0f,  0.0f,  0.0f},  glm::vec2{1.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{-1.f,  1.f, -1.f}, glm::vec3{-1.0f,  0.0f,  0.0f},  glm::vec2{1.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{-1.f, -1.f, -1.f}, glm::vec3{-1.0f,  0.0f,  0.0f},  glm::vec2{0.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{-1.f, -1.f, -1.f}, glm::vec3{-1.0f,  0.0f,  0.0f},  glm::vec2{0.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{-1.f, -1.f,  1.f}, glm::vec3{-1.0f,  0.0f,  0.0f},  glm::vec2{0.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{-1.f,  1.f,  1.f}, glm::vec3{-1.0f,  0.0f,  0.0f},  glm::vec2{1.0f, 0.0f}},

		Sunset::Vertex{glm::vec3{ 1.f,  1.f,  1.f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{1.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{ 1.f,  1.f, -1.f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{1.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{ 1.f, -1.f, -1.f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{0.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{ 1.f, -1.f, -1.f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{0.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{ 1.f, -1.f,  1.f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{0.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{ 1.f,  1.f,  1.f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{1.0f, 0.0f}},

		Sunset::Vertex{glm::vec3{-1.f, -1.f, -1.f},  glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{0.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{ 1.f, -1.f, -1.f},  glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{1.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{ 1.f, -1.f,  1.f},  glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{1.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{ 1.f, -1.f,  1.f},  glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{1.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{-1.f, -1.f,  1.f},  glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{0.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{-1.f, -1.f, -1.f},  glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{0.0f, 1.0f}},

		Sunset::Vertex{glm::vec3{-1.f,  1.f, -1.f},  glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{0.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{ 1.f,  1.f, -1.f},  glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{1.0f, 1.0f}},
		Sunset::Vertex{glm::vec3{ 1.f,  1.f,  1.f},  glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{1.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{ 1.f,  1.f,  1.f},  glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{1.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{-1.f,  1.f,  1.f},  glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{0.0f, 0.0f}},
		Sunset::Vertex{glm::vec3{-1.f,  1.f, -1.f},  glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{0.0f, 1.0f}}
	};

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
	{
		InitTextures(m_Textures, names, std::make_index_sequence<std::variant_size_v<TextureType>>{});
		m_Mesh = std::make_unique<Mesh>(vertices, m_Textures);
	}

	MeshComponent::~MeshComponent()
	{
		for (uint8_t i = 0; i < m_Textures.size(); ++i)
		{
			glDeleteTextures(1, &(m_Textures[i].id));
		}
	}

	Mesh* MeshComponent::operator()()
	{
		return m_Mesh.get();
	}
}

