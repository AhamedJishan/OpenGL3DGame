#pragma once
#include <vector>

#include "DataStructs/DataStructs.h"
#include "Shaders/Shader.h"

namespace OG3D
{
	class TerrainMesh
	{
	public:
		TerrainMesh(std::vector<std::vector<float>>& heightMap, float MinHeight, float MaxHeight)
		{
			m_width = heightMap[0].size();
			m_depth = heightMap.size();
			m_minHeight = MinHeight;
			m_maxHeight = MaxHeight;
			InitVertices(heightMap);
			InitIndices();
			SetupGlContext();
		}

		void Draw(Shader& shader);
		
		float GetMinHeight() { return m_minHeight; }
		float GetMaxHeight() { return m_maxHeight; }

	private:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		int m_width;
		int m_depth;
		float m_minHeight;
		float m_maxHeight;

		unsigned int VAO, VBO, EBO;

		void InitVertices(std::vector<std::vector<float>>& heightMap);
		void InitIndices();
		void SetupGlContext();
	};
}