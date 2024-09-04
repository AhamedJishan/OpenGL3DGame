#pragma once

#include <glad/glad.h>
#include "RawModel.h"

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

		void Render(RawModel& model)
		{
			unsigned int a = model.GetVaoID();
			unsigned int b = model.GetIndicesCount();
			glBindVertexArray(model.GetVaoID());
			glDrawElements(GL_TRIANGLES, model.GetIndicesCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	};
}