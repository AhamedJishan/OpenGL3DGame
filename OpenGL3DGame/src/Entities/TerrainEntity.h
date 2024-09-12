#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Terrain/Terrain.h"

namespace OG3D
{
	class TerrainEntity
	{
	public:
		TerrainEntity(BaseTerrain& terrain,
			glm::vec3 position = glm::vec3(0.0f),
			glm::vec3 rotation = glm::vec3(0.0f),
			glm::vec3 scale = glm::vec3(1.0f))
			:m_Terrain(terrain), m_Position(position), m_Rotation(rotation), m_Scale(scale)
		{
			Update();
		}
		~TerrainEntity() = default;

		// Getters
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_Scale; }
		glm::mat4& GetModelMatrix() { return m_ModelMatrix; }
		BaseTerrain& GetTerrain() const { return m_Terrain; }

		// Setters
		void SetPosition(const glm::vec3& position) { m_Position = position;	Update(); }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation;	Update(); }
		void SetScale(const glm::vec3& scale) { m_Scale = scale;			Update(); }

		// Increment/Decrement Position, Rotaion, Scale
		void Translate(const glm::vec3& delta) { m_Position += delta;	Update(); }
		void Rotate(const glm::vec3& delta) { m_Rotation += delta;	Update(); }
		void Scale(const glm::vec3& scaleFactor) { m_Scale += scaleFactor; Update(); }

		void Update()
		{
			m_ModelMatrix = glm::mat4(1.0f);
			m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
			m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
		}

	private:
		BaseTerrain& m_Terrain;
		glm::vec3 m_Position, m_Rotation, m_Scale;
		glm::mat4 m_ModelMatrix;
	};
}