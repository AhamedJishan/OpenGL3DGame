#pragma once

#include <vector>

#include <glad/glad.h>

#include "Window.h"
#include "Entities/Material.h"
#include "DataStructs/DataStructs.h"
#include "Entities/Entity.h"
#include "Entities/Camera.h"
#include "Entities/Light.h"

namespace OG3D
{
	class Renderer
	{
	private:
		const float FOV = 70.0f;
		const float NEAR_PLANE = 0.1f;
		const float FAR_PLANE = 100.0f;

		// For now there is one light for the Renderer but later on there needs to be a list of lights
		Light* m_Light;
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

		void Render(Entity& entity, Material& material)
		{
			material.shader.Use();
			material.shader.SetMat4("model", entity.GetModelMatrix());
			material.shader.SetMat4("view", m_Camera.GetViewMatrix());
			material.shader.SetMat4("projection", m_ProjectionMatrix);

			material.shader.SetVec3("viewPos", m_Camera.Position);

			material.shader.SetVec3("material.specularColor", material.specularColor);
			material.shader.SetFloat("material.shineDamper", material.shineDamper);
			material.shader.SetFloat("material.reflectivity", material.reflectivity);

			if (m_Light != nullptr)
			{
				material.shader.SetVec3("light.position", m_Light->Position);
				material.shader.SetVec3("light.color", m_Light->Color);
			}
			
			entity.GetModel().Draw(material.shader);
		}

		void AddLight(Light* light)
		{
			m_Light = light;
		}
	};
}