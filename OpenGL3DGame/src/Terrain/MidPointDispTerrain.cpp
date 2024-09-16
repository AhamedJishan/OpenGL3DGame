#include "MidPointDispTerrain.h"

#include "TerrainMesh.h"
#include "Utils/Random.h"

namespace OG3D
{
	void MidPointDispTerrain::GenerateMidPointDisplacement(int TerrainSize, float Smoothness, float MinHeight, float MaxHeight)
	{
		m_terrainSize = TerrainSize;
		m_minHeight = MinHeight;
		m_maxHeight = MaxHeight;

		m_heightMap.resize(m_terrainSize, std::vector<float>(m_terrainSize));

		GenerateMidPointDisplacementF32(Smoothness);

		m_terrainMesh = new TerrainMesh(m_heightMap, MinHeight, MaxHeight);
	}

	void MidPointDispTerrain::GenerateMidPointDisplacementF32(float Smoothness)
	{
		int rectSize = m_terrainSize;
		float curHeight = (float)rectSize / 2.0f;
		float heightReducefactor = pow(2.0f, -Smoothness);

		while (rectSize > 0)
		{
			DiamondStep(rectSize, curHeight);
			SquareStep(rectSize, curHeight);

			rectSize /= 2.0f;
			curHeight *= heightReducefactor;
		}
	}

	void MidPointDispTerrain::DiamondStep(int RectSize, float HeightRange)
	{
		Random& random = Random::GetInstance();
		int halfRectSize = RectSize / 2;

		for (int y = 0; y < m_terrainSize; y += RectSize)
		{
			for (int x = 0; x < m_terrainSize; x += RectSize)
			{
				int next_x = (x + RectSize) % m_terrainSize;
				int next_y = (y + RectSize) % m_terrainSize;

				float topLeft = m_heightMap[y][x];
				float topRight = m_heightMap[y][next_x];
				float bottomLeft = m_heightMap[next_y][x];
				float bottomRight = m_heightMap[next_y][next_x];

				int mid_x = x + halfRectSize;
				int mid_y = y + halfRectSize;

				float randValue = random.RandomFloat(HeightRange, -HeightRange);
				float midPoint = (topLeft + topRight + bottomLeft + bottomRight) / 4.0f;

				m_heightMap[mid_y][mid_x] = midPoint + randValue;
			}
		}
	}

	void MidPointDispTerrain::SquareStep(int RectSize, float HeightRange)
	{
		Random& random = Random::GetInstance();
		int halfRectSize = RectSize / 2;

		for (int y = 0; y < m_terrainSize; y += RectSize)
		{
			for (int x = 0; x < m_terrainSize; x += RectSize)
			{
				int next_x = (x + RectSize) % m_terrainSize;
				int next_y = (y + RectSize) % m_terrainSize;

				int mid_x = x + halfRectSize;
				int mid_y = y + halfRectSize;
				
				int prev_mid_x = (x - halfRectSize + m_terrainSize) % m_terrainSize;
				int prev_mid_y = (y - halfRectSize + m_terrainSize) % m_terrainSize;

				float curTopLeft = m_heightMap[y][x];
				float curTopRight = m_heightMap[y][next_x];
				float curCenter = m_heightMap[mid_y][mid_x];
				float prevYCenter = m_heightMap[prev_mid_y][mid_x];
				float curBottomLeft = m_heightMap[next_y][x];
				float prevXCenter = m_heightMap[mid_y][prev_mid_x];

				float curLeftMid = (curTopLeft + curCenter + curBottomLeft + prevXCenter) / 4.0f + random.RandomFloat(-HeightRange, HeightRange);
				float curTopMid = (curTopLeft + curCenter + curTopRight + prevYCenter) / 4.0f + random.RandomFloat(-HeightRange, HeightRange);

				m_heightMap[y][mid_x] = curTopMid;
				m_heightMap[mid_y][x] = curLeftMid;
			}
		}
	}
}