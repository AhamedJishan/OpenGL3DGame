#pragma once

#include <glad/glad.h>

namespace OG3D
{
	class RawModel
	{
	public:
		RawModel(unsigned int vaoID, unsigned int vboID, unsigned int eboID, unsigned int indicesCount)
			: m_vaoID(vaoID), m_vboID(vboID), m_eboID(eboID), m_indicesCount(indicesCount)
		{
		}
		~RawModel()
		{
			glDeleteBuffers(1, &m_eboID);
			glDeleteBuffers(1, &m_vboID);
			glDeleteVertexArrays(1, &m_vaoID);
		}

		unsigned int GetVaoID() const { return m_vaoID; }
		unsigned int GetIndicesCount() const { return m_indicesCount; }

	private:
		unsigned int m_vaoID;
		unsigned int m_vboID;
		unsigned int m_eboID;
		unsigned int m_indicesCount;
	};
}