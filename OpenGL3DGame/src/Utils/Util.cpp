#include "Util.h"

#include <fstream>
#include <iostream>

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
}