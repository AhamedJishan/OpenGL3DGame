#pragma once

#include <glad/glad.h>
#include "Model/RawModel.h"
#include "Shaders/Shader.h"
#include "Textures/Texture.h"
#include "Entities/Entity.h"

namespace OG3D
{
	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		void Prepare()
		{
			glClearColor(.1f, .1f, .1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void Render(Entity& entity, Shader& shader, Texture& texture)
		{
			shader.Use();
			shader.SetMat4("model", entity.GetModelMatrix());
			texture.Use();

			glBindVertexArray(entity.GetModel().GetVaoID());
			glDrawElements(GL_TRIANGLES, entity.GetModel().GetIndicesCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		void Render(RawModel& model, Shader& shader, Texture& texture)
		{
			shader.Use();
			texture.Use();

			glBindVertexArray(model.GetVaoID());
			glDrawElements(GL_TRIANGLES, model.GetIndicesCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	};
}