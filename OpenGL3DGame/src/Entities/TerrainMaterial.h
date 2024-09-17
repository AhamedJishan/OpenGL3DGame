#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "Shaders/Shader.h"

namespace OG3D
{
	struct TextureTile
	{
		unsigned int textureID;
		float height;
	};


	class TerrainMaterial
	{
	private:
		const int MAX_NUM_TEXTURES = 4;
	public:
		Shader& shader;
		std::vector<TextureTile> textures;
		glm::vec3 specularColor;
		float textureTileSize;
		float shineDamper;
		float reflectivity;

		TerrainMaterial(Shader& Shader, float TextureTileSize)
			:shader(Shader), textureTileSize(TextureTileSize)
		{
			specularColor = glm::vec3(0.0f);
			shineDamper = 1;
			reflectivity = 0.0f;
		}
		~TerrainMaterial()
		{
			if (textures.size() > 0)
			{
				for (int i = 0; i < textures.size(); i++)
				{
					glDeleteTextures(1, &textures[i].textureID);
				}
			}
		}

		//TerrainMaterial(glm::vec3 SpecularColor, int ShineDamper, float Reflectivity, Shader& Shader)
		//	:specularColor(SpecularColor), shineDamper(ShineDamper), reflectivity(Reflectivity), shader(Shader)
		//{
		//}

		void AddTextureTile(unsigned int TextureID, float Height)
		{
			if (textures.size() >= MAX_NUM_TEXTURES)
			{
				std::cout << "Max number of texture tiles added!\n";
				return;
			}

			TextureTile textureTile;
			textureTile.textureID = TextureID;
			textureTile.height = Height;

			textures.push_back(textureTile);
		}
	};
}