#pragma once

#include "RawModel.h"

#include <glad/glad.h>

namespace OG3D
{
	class Loader
	{
	public:
		Loader() = default;
		~Loader() = default;

		RawModel LoadRawModel(float positions[], unsigned int positionsLength, unsigned int indices[], unsigned int indicesLength)
		{
			unsigned int VAO, VBO, EBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, positionsLength, positions, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength, indices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			unsigned int vertexCount = positionsLength / 3;

			return RawModel(VAO, VBO, EBO, indicesLength);
		}
	};
}