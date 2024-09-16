#pragma once
#include "Terrain.h"

namespace OG3D
{
	class MidPointDispTerrain : public BaseTerrain
	{
	public:
		MidPointDispTerrain() {}

		void GenerateMidPointDisplacement(int TerrainSize, float Smoothness, float MinHeight, float MaxHeight);

	private:
		void GenerateMidPointDisplacementF32(float Smoothness);

		void DiamondStep(int RectSize, float HeightRange);
		void SquareStep(int RectSize, float HeightRange);
	};
}