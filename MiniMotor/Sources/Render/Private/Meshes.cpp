#include "Meshes.h"
#include "OpenGLShader.h"
#include "Event.h"

#include <glad/glad.h>

Mesh::Mesh(vertexList _vertices, indicesList _indices/*, texturelist _textures*/)
	: vertices(_vertices)
	, indices(_indices)
	//, textures(_textures)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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
	//uint32_t diffuseNr = 1;
	//uint32_t specularNr = 1;
	//for (uint32_t i = 0; i < textures.size(); ++i)
	//{
	//	glActiveTexture(GL_TEXTURE0 + i);
	//	std::string number;
	//	std::string name;
	//	std::visit(Overloaded(
	//	[&](TTexture::Diffuse arg)
	//	{
	//		name = arg.name();
	//		number = std::to_string(diffuseNr++);
	//	},
	//	[&](TTexture::Specular arg)
	//	{
	//		name = arg.name();
	//		number = std::to_string(specularNr++);
	//		
	//	}), textures[i].type);

	//	shader->Set1I(("material." + name + number).c_str(), i);
	//	glBindTexture(GL_TEXTURE_2D, textures[i].id);
	//}
	//glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	// todo : for the moment I don't have any ebo...
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
