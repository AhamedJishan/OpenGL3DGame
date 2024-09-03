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

		RawModel LoadRawModel(float positions[], unsigned int positionsLength)
		{
			unsigned int VAO, VBO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, positionsLength, positions, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			unsigned int vertexCount = positionsLength / 3;

			return RawModel(VAO, VBO, vertexCount);
		}
	};
}