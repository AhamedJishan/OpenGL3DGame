#pragma once
#include "Terrain.h"

#include <glm/glm.hpp>

namespace OG3D
{
	class FaultFormationTerrain : public BaseTerrain
	{
	public:
		FaultFormationTerrain() {}

		void GenerateFaultFormationTerrain(int TerrainSize, int Iterations, float MinHeight, float MaxHeight);

	private:
		void CreateFaultFormationInternal(int Iterations, float MinHeight, float MaxHeight);
		void GenRandomPoints(glm::vec2& p1, glm::vec2& p2);
	};
}