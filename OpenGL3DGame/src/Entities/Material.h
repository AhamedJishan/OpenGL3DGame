#pragma once

#include <glm/glm.hpp>

#include "Shaders/Shader.h"

namespace OG3D
{
	class Material
	{
	public:
		Shader& shader;
		glm::vec3 specularColor;
		float shineDamper;
		float reflectivity;

		Material(Shader& Shader)
			:shader(Shader)
		{
			specularColor = glm::vec3(0.0f);
			shineDamper = 1;
			reflectivity = 0.0f;
		}

		Material(glm::vec3 SpecularColor, int ShineDamper, float Reflectivity, Shader& Shader)
			:specularColor(SpecularColor), shineDamper(ShineDamper), reflectivity(Reflectivity), shader(Shader)
		{
		}
	};
}