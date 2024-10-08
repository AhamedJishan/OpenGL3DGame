#pragma once

#include <iostream>

#include "DataStructs/DataStructs.h"
#include <stb_image.h>

#include <glad/glad.h>

namespace OG3D
{
	class Loader
	{
	private:
		// Private constructor and destructor to prevent direct instantiation.
		Loader() = default;
		~Loader() = default;

	public:
		// Delete the copy constructor and assignment operator to prevent copying.
		Loader(const Loader&) = delete;
		Loader& operator=(const Loader&) = delete;

		// Static method to provide access to the singleton instance.
		static Loader& GetInstance()
		{
			static Loader instance; // Guaranteed to be lazy-initialized and destroyed.
			return instance;
		}

		unsigned int LoadTexture(const char* filepath, bool shouldFlipVertically = false)
		{
			stbi_set_flip_vertically_on_load(shouldFlipVertically);
			unsigned int ID;
			glGenTextures(1, &ID);

			int width, height, nrComponents;
			unsigned char* data = stbi_load(filepath, &width, &height, &nrComponents, 0);
			if (data)
			{
				GLenum format;
				if (nrComponents == 1)
					format = GL_RED;
				else if (nrComponents == 3)
					format = GL_RGB;
				else if (nrComponents == 4)
					format = GL_RGBA;

				glBindTexture(GL_TEXTURE_2D, ID);
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "Failed to load texture at path: " << filepath << "\n";
			}

			stbi_image_free(data);
			return ID;
		}
	};
}