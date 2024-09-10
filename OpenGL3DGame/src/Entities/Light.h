#pragma once

#include <glm/glm.hpp>

namespace OG3D
{
	class Light
	{
	public:
		glm::vec3 Position;
		glm::vec3 Color;
		glm::vec3 Ambient;

	public:
		Light(glm::vec3 position, glm::vec3 color, glm::vec3 ambient)
			:Position(position), Color(color), Ambient(ambient)
		{

		}
	};
}