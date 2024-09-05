#pragma once

#include "Model/RawModel.h"
#include "Model/Primitive.h"
#include "Textures/Texture.h"
#include "stbi/stb_image.h"

#include <glad/glad.h>

namespace OG3D
{
	class Loader
	{
	public:
		Loader() = default;
		~Loader() = default;

		RawModel GenerateRawModel(Primitive& primitive)
		{
			unsigned int VAO, VBO, EBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, primitive.GetVerticesCount() * sizeof(float), primitive.GetVertices(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, primitive.GetIndicesCount() * sizeof(unsigned int), primitive.GetIndices(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)) );

			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			return RawModel(VAO, VBO, EBO, primitive.GetIndicesCount());
		}

		RawModel GenerateRawModel(float vertices[], unsigned int verticesCount, unsigned int indices[], unsigned int indicesCount)
		{
			unsigned int VAO, VBO, EBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(float), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			return RawModel(VAO, VBO, EBO, indicesCount);
		}
	

		Texture LoadTexture(const char* filepath)
		{
			stbi_set_flip_vertically_on_load(true);
			unsigned int ID;
			glGenTextures(1, &ID);

			glBindTexture(GL_TEXTURE_2D, ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			int width, height, nrChannels;
			unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);

			GLint format;
			if (nrChannels == 3) format = GL_RGB;
			else if (nrChannels == 4) format = GL_RGBA;
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "Failed to load texture at path: " << filepath << "\n";
			}

			stbi_image_free(data);

			return Texture(ID);
		}
	};
}