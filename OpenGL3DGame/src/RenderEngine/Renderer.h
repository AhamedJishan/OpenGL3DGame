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

		void Render(RawModel model)
		{
			glBindVertexArray(model.GetVaoID());
			glDrawArrays(GL_TRIANGLES, 0, model.GetVertexCount());
			glBindVertexArray(0);
		}
	};
}