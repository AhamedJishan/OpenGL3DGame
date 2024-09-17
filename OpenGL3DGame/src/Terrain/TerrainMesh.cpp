#include "TerrainMesh.h"
#include "Utils/Util.h"
#include "RenderEngine/Loader.h"

namespace OG3D
{
	void TerrainMesh::InitVertices(std::vector<std::vector<float>>& heightMap)
	{
		m_vertices.resize(m_width * m_depth);

		float minMaxHeightDelta = m_maxHeight - m_minHeight;
		Normalize2DArray(heightMap, m_minHeight, m_maxHeight);

		for (int z = 0; z < m_depth; z++)
		{
			for (int x = 0; x < m_width; x++)
			{
				m_vertices[m_width * z + x].Position.x = x;
				m_vertices[m_width * z + x].Position.y = heightMap[z][x];
				m_vertices[m_width * z + x].Position.z = z;
				m_vertices[m_width * z + x].Normal.x = 0.0f;
				m_vertices[m_width * z + x].Normal.y = 1.0f;
				m_vertices[m_width * z + x].Normal.z = 0.0f;
				m_vertices[m_width * z + x].TexCoords.x = x / (float)(m_width - 1);
				m_vertices[m_width * z + x].TexCoords.y = z / (float)(m_depth - 1);
			}
		}
	}

	void TerrainMesh::InitIndices()
	{
		int numQuads = (m_width - 1) * (m_depth - 1);
		m_indices.resize(6 * numQuads);

		int pointer = 0;
		for (int row = 0; row < m_depth-1; row++)
		{
			for (int col = 0; col < m_width-1; col++)
			{
				int TopLeft = row * m_width + col;
				int TopRight = TopLeft + 1;
				int BottomLeft = (row + 1) * m_width + col;
				int BottomRight = BottomLeft + 1;

				m_indices[pointer++] = TopLeft;
				m_indices[pointer++] = BottomLeft;
				m_indices[pointer++] = TopRight;
				m_indices[pointer++] = BottomLeft;
				m_indices[pointer++] = BottomRight;
				m_indices[pointer++] = TopRight;
			}
		}
	}

	void TerrainMesh::SetupGlContext()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}

	void TerrainMesh::Draw(Shader& shader)
	{
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}