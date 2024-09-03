#include <iostream>
#include <glad/glad.h>

#include "RenderEngine/Window.h"
#include "RenderEngine/Loader.h"
#include "RenderEngine/Renderer.h"
#include "RenderEngine/RawModel.h"

using namespace OG3D;

// Positions for a quad (rectangle) with vertex positions specified
float positions[] = {
	// Vertex positions for two triangles making up the quad
	// First triangle
	-0.5f, -0.5f, 0.0f, // Bottom-left
	0.5f, -0.5f, 0.0f,  // Bottom-right
	-0.5f, 0.5f, 0.0f,  // Top-left

	// Second triangle
	0.5f, -0.5f, 0.0f,  // Bottom-right
	0.5f, 0.5f, 0.0f,   // Top-right
	-0.5f, 0.5f, 0.0f   // Top-left
};


int main()
{
	Window window(1280, 720, "My Game");

	Loader loader;
	Renderer renderer;
	
	RawModel model = loader.LoadRawModel(positions, sizeof(positions) / (sizeof(float)));

	while (!window.IsCloseRequested())
	{

		renderer.Prepare();
		
		renderer.Render(model);

		window.Update();
	}
}