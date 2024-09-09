#pragma once

#include <glad/glad.h>

#include "Window.h"
#include "Shaders/Shader.h"
#include "DataStructs/DataStructs.h"
#include "Entities/Entity.h"
#include "Entities/Camera.h"

namespace OG3D
{
	class Renderer
	{
	private:
		const float FOV = 70.0f;
		const float NEAR_PLANE = 0.1f;
		const float FAR_PLANE = 100.0f;

		Camera& m_Camera;
		glm::mat4 m_ProjectionMatrix;

	public:
		Renderer(Camera& camera, Window& window)
			:m_Camera(camera)
		{
			m_ProjectionMatrix = glm::perspective(FOV, window.GetAspectRatio(), NEAR_PLANE, FAR_PLANE);
		}
		~Renderer() = default;

		void Prepare()
		{
			glClearColor(.1f, .1f, .1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Render(Entity& entity, Shader& shader)
		{
			shader.Use();
			shader.SetMat4("model", entity.GetModelMatrix());
			shader.SetMat4("view", m_Camera.GetViewMatrix());
			shader.SetMat4("projection", m_ProjectionMatrix);
			
			entity.GetModel().Draw(shader);
		}
	};
}