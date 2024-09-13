#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "TerrainMesh.h"

namespace OG3D
{
	class BaseTerrain
	{
	public:
		BaseTerrain()
		{
		}
		virtual ~BaseTerrain()
		{
			if (m_terrainMesh != nullptr)
			{
				delete(m_terrainMesh);
			}
		}

		void GenerateTerrain(const char* heightMapFilepath,float MinHeight, float MaxHeight);
		TerrainMesh* GetTerrainMesh() { return m_terrainMesh; }

	protected:
		int m_terrainSize = 0;
		float m_minHeight, m_maxHeight;
		std::vector<std::vector<float>> m_heightMap;
		TerrainMesh* m_terrainMesh;

		void LoadHeightMapFromFile(const char* filepath);
	};
}