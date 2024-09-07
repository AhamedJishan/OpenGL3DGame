#pragma once

#include "Primitive.h"
#include <vector>

namespace OG3D
{
	class Cube : public Primitive
	{
	public:
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;

		const unsigned int GetVerticesCount() const override { return m_Vertices.size(); }
		const unsigned int GetIndicesCount() const override { return m_Indices.size(); }
		const float* GetVertices() const override { return m_Vertices.data(); }
		const unsigned int* GetIndices() const override { return m_Indices.data(); }

	public:
		Cube()
		{
			// Vertices with positions and texture coordinates interleaved
			m_Vertices = {
				// Position              // Texture Coords
				-0.5f,  0.5f, -0.5f,    0.0f, 0.0f,  // Front face
				-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,    1.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,    0.0f, 0.0f,  // Back face
				-0.5f, -0.5f,  0.5f,    0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,    1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

				 0.5f,  0.5f, -0.5f,    0.0f, 0.0f,  // Right face
				 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,    1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

				-0.5f,  0.5f, -0.5f,    0.0f, 0.0f,  // Left face
				-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,    1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,    0.0f, 0.0f,  // Top face
				-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  // Bottom face
				-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,    1.0f, 0.0f
			};

			// Indices for drawing cube using triangles
			m_Indices = {
				0, 1, 3,  3, 1, 2,  // Front face
				4, 5, 7,  7, 5, 6,  // Back face
				8, 9, 11, 11, 9, 10, // Right face
				12, 13, 15, 15, 13, 14, // Left face
				16, 17, 19, 19, 17, 18, // Top face
				20, 21, 23, 23, 21, 22  // Bottom face
			};
		}

		~Cube() = default;
	};
}
