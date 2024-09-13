#include <iostream>

#include "Terrain.h"

#include "Utils/Util.h"

namespace OG3D
{
	void BaseTerrain::GenerateTerrain(const char* heightMapFilepath,float MinHeight, float MaxHeight)
	{
		m_minHeight = MinHeight;
		m_maxHeight = MaxHeight;
		LoadHeightMapFromFile(heightMapFilepath);
		m_terrainMesh = new TerrainMesh(m_heightMap, m_minHeight, m_maxHeight);
	}

	void BaseTerrain::LoadHeightMapFromFile(const char* filepath)
	{
		int fileSize = 0;
		std::vector<char> data = ReadBinaryFile(filepath, fileSize);

		if (fileSize % sizeof(float) != 0)
		{
			std::cout << "Invalid Heightmap: " << filepath << "\n";
			return;
		}

		m_terrainSize = sqrt(fileSize / sizeof(float));

		// Initialize heightMap with the correct size
		m_heightMap.resize(m_terrainSize, std::vector<float>(m_terrainSize));

		int index = 0;
		for (int z = 0; z < m_terrainSize; z++) {
			for (int x = 0; x < m_terrainSize; x++)
			{
				m_heightMap[z][x] = *reinterpret_cast<float*>(&data[4 * index]);
				++index;
			}
		}
	}
}