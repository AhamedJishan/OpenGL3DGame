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

		void GenerateTerrain(const char* heightMapFilepath, int worldScale = 1);
		TerrainMesh* GetTerrainMesh() { return m_terrainMesh; }

	private:
		int m_terrainSize = 0;
		std::vector<std::vector<float>> m_heightMap;
		TerrainMesh* m_terrainMesh;

		void LoadHeightMapFromFile(const char* filepath);
	};
}