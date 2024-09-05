#include "RenderEngine.h"
using namespace OG3D;

int main()
{
	Window window(1280, 720, "My Game");

	Loader loader;
	Renderer renderer;

	Shader shader("src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");
	Texture texture = loader.LoadTexture("res/Textures/awesomeface.png");
	
	Quad quad;
	RawModel model = loader.GenerateRawModel(quad);
	  
	while (!window.IsCloseRequested())
	{
		renderer.Prepare();

		shader.Use();
		texture.Use();
		renderer.Render(model);

		window.Update();
	}
}