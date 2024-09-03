#pragma once

#include <glad/glad.h>

namespace OG3D
{
	class RawModel
	{
	public:
		RawModel(unsigned int vaoID, unsigned int vboID, unsigned int vertexCount)
			: m_vaoID(vaoID), m_vboID(vboID), m_vertexCount(vertexCount)
		{
		}
		~RawModel()
		{
			glDeleteBuffers(1, &m_vboID);
			glDeleteVertexArrays(1, &m_vaoID);
		}

		unsigned int GetVaoID() const { return m_vaoID; }
		unsigned int GetVertexCount() const { return m_vertexCount; }

	private:
		unsigned int m_vaoID;
		unsigned int m_vboID;
		unsigned int m_vertexCount;
	};
}