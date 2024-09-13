#pragma once
#include <vector>

namespace OG3D
{
	std::vector<char> ReadBinaryFile(const char* pFilename, int& size);

	void Normalize2DArray(std::vector<std::vector<float>>& array2d, float minRange, float maxRange);
}