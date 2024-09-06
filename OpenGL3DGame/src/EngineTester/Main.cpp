#include "Engine.h"
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
	Entity planeEntity(model);
	  
	while (!window.IsCloseRequested())
	{
		renderer.Prepare();

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.GetAspectRatio(), 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0), glm::vec3(0.0f, 1.0f, 0.0f));
		shader.SetMat4("projection", projection);
		shader.SetMat4("view", view);
		
		planeEntity.Rotate( glm::vec3(0.0f, glfwGetTime(), 0.0f) );
		renderer.Render(planeEntity, shader, texture);

		window.Update();
	}
}