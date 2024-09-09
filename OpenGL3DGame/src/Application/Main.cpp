#include "Engine.h"
#include <string>

using namespace OG3D;

// Function identifiers ---------------------------
void CameraMovement(Camera& camera, Window& window);

int main()
{
	Window window(1280, 720, "My Game");
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	Loader loader;
	Renderer renderer(camera, window);

	Shader shader("src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");

	Model flatScene("res/Models/FlatScene/FlatScene.obj");
	Entity SceneEntity(flatScene);

	while (!window.IsCloseRequested())
	{
		Time::Tick();

		CameraMovement(camera, window);

		renderer.Prepare();
		
		SceneEntity.Rotate( glm::vec3(0.0f, 0.05f, 0.0f));
		renderer.Render(SceneEntity, shader);

		window.Update();
	}
}

// Makes camera move from WASD keys
void CameraMovement(Camera& camera, Window& window)
{
	float speed = 5 * Time::GetDeltaTime();

	if (glfwGetKey(window.GetGlfwWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Position += camera.Forward * speed;
	}
	if (glfwGetKey(window.GetGlfwWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Position -= camera.Right * speed;
	}
	if (glfwGetKey(window.GetGlfwWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Position -= camera.Forward * speed;
	}
	if (glfwGetKey(window.GetGlfwWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Position += camera.Right * speed;
	}

	// Update the Camera ---------------------------------------------
	camera.Update();
}