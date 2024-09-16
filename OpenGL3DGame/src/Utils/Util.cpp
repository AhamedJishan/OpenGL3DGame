#include "Util.h"

#include <fstream>
#include <iostream>
#include <cmath>

namespace OG3D
{
    std::vector<char> ReadBinaryFile(const char* pFilename, int& size)
    {
        std::ifstream file(pFilename, std::ios::binary | std::ios::ate);
        if (!file)
        {
            std::cout << "Error opening file: " << pFilename << "\n";
            return {};
        }

        size = static_cast<int>(file.tellg());
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size); // Allocate buffer of appropriate size
        if (!file.read(buffer.data(), size)) { // Read file data into buffer
            std::cerr << "Error reading file: " << pFilename << std::endl;
            return {};
        }

        file.close();

        return buffer;
    }

    void Normalize2DArray(std::vector<std::vector<float>>& array2d, float minRange, float maxRange)
    {
        float min = array2d[0][0];
        float max = array2d[0][1];

        for (int x = 0; x < array2d.size(); x++)
        {
            for (int y = 0; y < array2d[0].size(); y++)
            {
                if (array2d[x][y] < min) min = array2d[x][y];
                if (array2d[x][y] > max) max = array2d[x][y];
            }
        }

        float minMaxDelta = max - min;
        float minMaxRange = maxRange - minRange;

        for (int x = 0; x < array2d.size(); x++)
        {
            for (int y = 0; y < array2d[0].size(); y++)
            {
                array2d[x][y] = (array2d[x][y] - min) / minMaxDelta * minMaxRange + minRange;
            }
        }
    }
}