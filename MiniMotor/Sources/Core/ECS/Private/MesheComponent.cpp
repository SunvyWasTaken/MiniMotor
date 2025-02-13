
#include "MesheComponent.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>


namespace
{
	// Todo : this should be temporary
	std::vector<Vertex> vertices = {
		// positions						// normals					// texture coords
		Vertex{FVec3{-0.5f, -0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{ 0.5f, -0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{ 0.5f,  0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{ 0.5f,  0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{-0.5f,  0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{0.0f, 0.0f}},

		Vertex{FVec3{-0.5f, -0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{0.0f, 0.0f}},
		Vertex{FVec3{ 0.5f, -0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{1.0f, 0.0f}},
		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{1.0f, 1.0f}},
		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{1.0f, 1.0f}},
		Vertex{FVec3{-0.5f,  0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{0.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{0.0f, 0.0f}},

		Vertex{FVec3{-0.5f,  0.5f,  0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{-0.5f,  0.5f, -0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f, -0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f, -0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f,  0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{-0.5f,  0.5f,  0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{1.0f, 0.0f}},

		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{ 0.5f,  0.5f, -0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{ 0.5f, -0.5f, -0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{ 0.5f, -0.5f, -0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{ 0.5f, -0.5f,  0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{1.0f, 0.0f}},

		Vertex{FVec3{-0.5f, -0.5f, -0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{ 0.5f, -0.5f, -0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{ 0.5f, -0.5f,  0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{ 0.5f, -0.5f,  0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{-0.5f, -0.5f,  0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{-0.5f, -0.5f, -0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{0.0f, 1.0f}},

		Vertex{FVec3{-0.5f,  0.5f, -0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{ 0.5f,  0.5f, -0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{-0.5f,  0.5f,  0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{-0.5f,  0.5f, -0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{0.0f, 1.0f}}
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
}

MeshComponent::MeshComponent()
{
	BaseColor = Texture(LoadTexture("../../Ressources/SunsetBaseColor.jpg"), TTexture::Specular());
	SpecColor = Texture(LoadTexture("../../Ressources/SunsetSpec.png"), TTexture::Diffuse());
	TextureList textures = { SpecColor, BaseColor };

	mesh = std::make_unique<Mesh>(vertices, textures);
}

MeshComponent::~MeshComponent()
{
	glDeleteTextures(1, &BaseColor.id);
	glDeleteTextures(1, &SpecColor.id);
}

Mesh* MeshComponent::operator()()
{
	return mesh.get();
}

