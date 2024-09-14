#include "FaultFormationTerrain.h"

#include <cstdlib>

#include "Utils/Util.h"

namespace OG3D
{
	void FaultFormationTerrain::GenerateFaultFormationTerrain(int TerrainSize, int Iterations, float MinHeight, float MaxHeight, float filter)
	{
		m_terrainSize = TerrainSize;
		m_minHeight = MinHeight;
		m_maxHeight = MaxHeight;

		m_heightMap.resize(m_terrainSize, std::vector<float>(m_terrainSize));

		CreateFaultFormationInternal(Iterations, MinHeight, MaxHeight, filter);

		m_terrainMesh = new TerrainMesh(m_heightMap, m_minHeight, m_maxHeight);
	}

	void FaultFormationTerrain::CreateFaultFormationInternal(int Iterations, float MinHeight, float MaxHeight, float filter)
	{
		float deltaHeight = MaxHeight - MinHeight;

		for (int curIteration = 0; curIteration < Iterations; curIteration++)
		{
			float iterationRatio = curIteration / (float)Iterations;
			float height = MaxHeight - iterationRatio * deltaHeight;

			glm::vec2 p1, p2;
			GenRandomPoints(p1, p2);

			glm::vec2 faultDir = p2 - p1;

			for (int z = 0; z < m_terrainSize; z++)
			{
				for (int x = 0; x < m_terrainSize; x++)
				{
					glm::vec2 curPointToFaultDir(x - p1.x, z - p1.y);

					float crossProduct = curPointToFaultDir.x * faultDir.y - curPointToFaultDir.y * faultDir.x;

					if (crossProduct > 0)
					{
						float curHeight = m_heightMap[z][x];
						m_heightMap[z][x] = curHeight + height;
					}
				}
			}
		}
		ApplyFIRFilter(filter);
	}

	void FaultFormationTerrain::ApplyFIRFilter(float filter)
	{
		// left to right
		for (int z = 0; z < m_terrainSize; z++)
		{
			float prevValue = m_heightMap[z][0];
			for (int x = 1; x < m_terrainSize; x++)
			{
				prevValue = FIRFilterSinglePoint(x, z, prevValue, filter);
			}
		}

		// right to left
		for (int z = 0; z < m_terrainSize; z++)
		{
			float prevValue = m_heightMap[z][m_terrainSize - 1];
			for (int x = m_terrainSize - 2; x >= 0; x--)
			{
				prevValue = FIRFilterSinglePoint(x, z, prevValue, filter);
			}
		}

		// top to bottom
		for (int x = 0; x < m_terrainSize; x++)
		{
			float prevValue = m_heightMap[0][x];
			for (int z = 1; z < m_terrainSize; z++)
			{
				prevValue = FIRFilterSinglePoint(x, z, prevValue, filter);
			}
		}

		// bottom to top
		for (int x = 0; x < m_terrainSize; x++)
		{
			float prevValue = m_heightMap[m_terrainSize - 1][x];
			for (int z = m_terrainSize - 2; z >= 0; z--)
			{
				prevValue = FIRFilterSinglePoint(x, z, prevValue, filter);
			}
		}

	}

	float FaultFormationTerrain::FIRFilterSinglePoint(int x, int z, float prevValue, float filter)
	{
		float curValue = m_heightMap[z][x];
		float newValue = filter * prevValue + (1 - filter) * curValue;
		m_heightMap[z][x] = newValue;
		return newValue;
	}

	void FaultFormationTerrain::GenRandomPoints(glm::vec2& p1, glm::vec2& p2)
	{
		p1.x = rand() % m_terrainSize;
		p1.y = rand() % m_terrainSize;

		int counter = 0;
		do
		{
			p2.x = rand() % m_terrainSize;
			p2.y = rand() % m_terrainSize;

			if (counter++ >= 100)
			{
				std::cout << "Endless loop detected\n";
				break;
			}
		} while (p2==p1);
	}
}