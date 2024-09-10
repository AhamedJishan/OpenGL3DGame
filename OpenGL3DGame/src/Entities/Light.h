#pragma once

#include <glm/glm.hpp>

namespace OG3D
{
	class Light
	{
	public:
		glm::vec3 Position;
		glm::vec3 Color;

	public:
		Light(glm::vec3 position, glm::vec3 color)
			:Position(position), Color(color)
		{

		}
	};
}