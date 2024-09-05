#include "RenderEngine.h"
using namespace OG3D;

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float positions[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

int main()
{
	Window window(1280, 720, "My Game");

	Loader loader;
	Renderer renderer;
	Shader shader("src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");
	
	Quad quad;
	RawModel model = loader.GenerateRawModel(quad);

	while (!window.IsCloseRequested())
	{
		renderer.Prepare();

		shader.Use();
		renderer.Render(model);

		window.Update();
	}
}