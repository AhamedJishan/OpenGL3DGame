#pragma once

#include "Primitive.h"
#include <vector>

namespace OG3D
{
	class Quad : public Primitive
	{
	public:
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;

		const unsigned int GetVerticesCount() const override { return m_Vertices.size(); }
		const unsigned int GetIndicesCount() const override { return m_Indices.size(); }
		const float* GetVertices() const override { return m_Vertices.data(); }
		const unsigned int* GetIndices() const override { return m_Indices.data(); }

	public:
		Quad()
		{
			// Define the positions for a quad (two triangles)
			m_Vertices = {
				// Position				// Texture Coords
				-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,  // Top-left
				 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,  // Top-right
				 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,  // Bottom-right
				-0.5f, -0.5f, 0.0f,		0.0f, 0.0f   // Bottom-left
			};

			// Define indices for the quad (two triangles)
			m_Indices = {
				0, 1, 2,  // First triangle
				2, 3, 0   // Second triangle
			};
		}

		~Quad() = default;
	};
}
