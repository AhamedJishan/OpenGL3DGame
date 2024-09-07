#include "Engine.h"
#include <string>

using namespace OG3D;

int main()
{
	Window window(1280, 720, "My Game");
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	Loader loader;
	Renderer renderer(camera, window);

	Shader shader("src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");
	Texture texture = loader.LoadTexture("res/Textures/awesomeface.png");

	Cube cube;
	RawModel model = loader.GenerateRawModel(cube);
	Entity planeEntity(model);

	while (!window.IsCloseRequested())
	{
		Time::Tick();

		renderer.Prepare();
		
		planeEntity.Rotate( glm::vec3(0.1f, 0.2f, 0.0f));
		renderer.Render(planeEntity, shader, texture);

		window.Update();
	}
}