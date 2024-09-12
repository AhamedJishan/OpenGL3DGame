#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "TerrainMesh.h"

namespace OG3D
{
	class BaseTerrain
	{
	public:
		BaseTerrain(const char* heightMapFile, int worldScale)
		{
			InitTerrain(heightMapFile);
			m_terrainMesh = new TerrainMesh(m_heightMap, worldScale);
		}
		~BaseTerrain()
		{
			if (m_terrainMesh != nullptr)
			{
				delete(m_terrainMesh);
			}
		}

		TerrainMesh* GetTerrainMesh() { return m_terrainMesh; }

		glm::vec3 GetScale() { return m_scale; }
		void SetScale(glm::vec3 scale) { m_scale = scale; }

	private:
		glm::vec3 m_scale;
		int m_terrainSize = 0;
		std::vector<std::vector<float>> m_heightMap;
		TerrainMesh* m_terrainMesh;


		void InitTerrain(const char* heightMapFilepath);
		void LoadHeightMapFromFile(const char* filepath);
		float GetHeight(int x, int z) { return m_heightMap[z][x]; }
	};
}