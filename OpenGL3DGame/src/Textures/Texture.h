#pragma once

#include "glad/glad.h"

namespace OG3D
{
	class Texture
	{
	public:
		Texture(unsigned int id)
			:m_ID(id)
		{
		}
		~Texture() = default;

		void Use() { glBindTexture(GL_TEXTURE_2D, m_ID); }

		unsigned int GetID() { return m_ID; }

	private:
		unsigned int m_ID;
	};
}