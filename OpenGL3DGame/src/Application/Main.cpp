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
	Material material(glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, 1.0f, shader);

	Light light(glm::vec3(-3.0f, 1.0f, 3.0f), glm::vec3(1.0f));
	renderer.AddLight(&light);

	Model flatScene(PRIMITIVE_MONKEY);
	//Model flatScene("res/Models/FlatScene/FlatScene.obj");
	Entity SceneEntity(flatScene);

	while (!window.IsCloseRequested())
	{
		Time::Tick();

		CameraMovement(camera, window);

		renderer.Prepare();
		
		SceneEntity.Rotate( glm::vec3(0.0f, 0.05f, 0.0f));
		renderer.Render(SceneEntity, material);

		window.Update();
	}
}

// Makes camera move from WASD keys
void CameraMovement(Camera& camera, Window& window)
{
	float speed = 2 * Time::GetDeltaTime();

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

	if (glfwGetKey(window.GetGlfwWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.Position += camera.Up * speed;
	}
	if (glfwGetKey(window.GetGlfwWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera.Position -= camera.Up * speed;
	}

	if (glfwGetKey(window.GetGlfwWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.Yaw -= speed*40;
	}
	if (glfwGetKey(window.GetGlfwWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.Yaw += speed*40;
	}

	// Update the Camera ---------------------------------------------
	camera.Update();
}