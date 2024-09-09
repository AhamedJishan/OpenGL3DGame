#pragma once

#include <glm/glm.hpp>
#include <string>

namespace OG3D
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture
	{
		unsigned int ID;
		std::string type;
		std::string path;
	};
}