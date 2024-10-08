#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "DataStructs/DataStructs.h"
#include "Shaders/Shader.h"

namespace OG3D
{
	class Mesh
	{
	public:
		std::vector<Vertex>			vertices;
		std::vector<unsigned int>	indices;
		std::vector<Texture>		textures;

	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
		{
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;

			SetUp();
		}

		void Draw(Shader& shader)
		{
			if (textures.size() == 0)
			{
				shader.SetBool("useTexture", false);
			}
			else
			{
				shader.SetBool("useTexture", true);
				unsigned int diffuseNr = 1;
				unsigned int specularNr = 1;
				for (unsigned int i = 0; i < textures.size(); i++)
				{
					std::string number;
					std::string name = textures[i].type;
					if (name == "texture_diffuse")
					{
						number = std::to_string(diffuseNr++);
					}
					else if (name == "texture_specular")
					{
						number = std::to_string(specularNr++);
					}

					name = name + number;

					glActiveTexture(GL_TEXTURE0 + i);
					shader.SetInt(name, i);
					glBindTexture(GL_TEXTURE_2D, textures[i].ID);
				}
			}
			glActiveTexture(0);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	private:
		unsigned int VAO, VBO, EBO;

		void SetUp()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

			glBindVertexArray(0);
		}
	};
}