#pragma once

#include "Primitive.h"
#include <vector>

namespace OG3D
{
	class Triangle : public Primitive
	{
	public:
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;

		const unsigned int GetVerticesCount() const override { return m_Vertices.size(); }
		const unsigned int GetIndicesCount() const override { return m_Indices.size(); }
		const float* GetVertices() const override { return m_Vertices.data(); }
		const unsigned int* GetIndices() const override { return m_Indices.data(); }

	public:
		Triangle()
		{
			// Define the positions for an equilateral triangle
			m_Vertices = {
				// Position             // Texture Coords
				0.0f,  0.577f, 0.0f,  0.5f, 0.0f,  // Top vertex (approx sqrt(3)/3)
			   -0.5f, -0.288f, 0.0f,  0.0f, 1.0f,  // Bottom-left vertex (approx -sqrt(3)/6)
				0.5f, -0.288f, 0.0f,  1.0f, 1.0f   // Bottom-right vertex (approx -sqrt(3)/6)
			};

			// Define indices for the triangle
			m_Indices = {
				0, 1, 2  // Single triangle
			};
		}

		~Triangle() = default;
	};
}
