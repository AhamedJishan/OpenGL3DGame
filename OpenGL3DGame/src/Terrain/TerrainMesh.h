#pragma once
#include <vector>

#include "DataStructs/DataStructs.h"
#include "Shaders/Shader.h"

namespace OG3D
{
	class TerrainMesh
	{
	public:
		TerrainMesh(std::vector<std::vector<float>>& heightMap, int worldScale = 1)
		{
			m_width = heightMap[0].size();
			m_depth = heightMap.size();
			m_worldScale = worldScale;
			InitVertices(heightMap);
			InitIndices();
			SetupGlContext();
		}

		void Draw(Shader& shader);

	private:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		int m_width;
		int m_depth;
		int m_worldScale;

		unsigned int VAO, VBO, EBO;

		void InitVertices(std::vector<std::vector<float>>& heightMap);
		void InitIndices();
		void SetupGlContext();
	};
}