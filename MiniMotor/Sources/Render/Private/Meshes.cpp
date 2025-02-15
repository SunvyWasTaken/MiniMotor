#include "Meshes.h"
#include "OpenGLShader.h"
#include "Event.h"
#include "Typelists.h"

#include <glad/glad.h>

namespace Sunset
{
	Mesh::Mesh(const VertexList& _vertices, const TextureList& _textures)
		: Vertices(_vertices)
		, Textures(_textures)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void Mesh::Draw(ShaderOGL* shader) const
	{
		using NbrList = std::array<uint32_t, std::variant_size_v<TextureType>>;
		NbrList Nbr;
		Nbr.fill(1);

		for (uint32_t i = 0; i < std::variant_size_v<TextureType>; ++i)
		{
			if (!Textures[i].isValid)
				continue;

			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;
			std::string name;
			std::visit(
				[&](auto&& arg)
				{
					name = arg.name();
					number = std::to_string(Nbr[TypeIndex<std::decay_t<decltype(arg)>, TextureType>::value]++);
				}
			, Textures[i].type);

			shader->Set1I(("material." + name).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, Textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);

		// draw mesh
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, Vertices.size());
		// todo : for the moment I don't have any ebo...
		//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
