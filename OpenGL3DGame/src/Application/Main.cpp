#include "Engine.h"
#include <string>

using namespace OG3D;

// Function identifiers ---------------------------
void CameraMovement(Camera& camera, Window& window);
void CameraLook(Camera& camera, Window& window);

int main()
{
	Window window(1280, 720, "My Game");
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	Renderer renderer(camera, window);
	Loader& loader = Loader::GetInstance();

	Shader shader("src/Shaders/VertexShader.vert", "src/Shaders/FragmentShader.frag");
	Material material(glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, 1.0f, shader);

	Light light(glm::vec3(-3.0f, 1.0f, 3.0f), glm::vec3(1.0f), glm::vec3(0.15f));
	renderer.AddLight(&light);

	Model flatScene(PRIMITIVE_MONKEY);
	//Model flatScene("res/Models/FlatScene/FlatScene.obj");
	Entity SceneEntity(flatScene);

	//BaseTerrain baseTerrain;
	//baseTerrain.GenerateTerrain("res/HeightMaps/heightmap.save", 0.0, 50.0);
	//FaultFormationTerrain faultFormationTerrain;
	//faultFormationTerrain.GenerateFaultFormationTerrain(256, 100, 0.0, 50.0, 0.8);
	float minHeight = 0.0f;
	float maxHeight = 60.0f;
	MidPointDispTerrain midPointDispTerrain;
	midPointDispTerrain.GenerateMidPointDisplacement(256, 1.1f, minHeight, maxHeight);
	TerrainEntity terrain(midPointDispTerrain);
	
	Shader terrainShader("src/Shaders/TerrainVertexShader.vert", "src/Shaders/TerrainFragmentShader.frag");
	TerrainMaterial terrainMaterial(terrainShader, 15.0f);
	terrainMaterial.AddTextureTile(loader.LoadTexture("res/Textures/Terrain/ground_mud_d.jpg"), minHeight + 0.1 * (maxHeight-minHeight)/(float)4);
	terrainMaterial.AddTextureTile(loader.LoadTexture("res/Textures/Terrain/grass_ground_d.jpg"), minHeight + 2 * (maxHeight - minHeight) / (float)4);
	terrainMaterial.AddTextureTile(loader.LoadTexture("res/Textures/Terrain/mntn_dark_d.jpg"), minHeight + 3 * (maxHeight - minHeight) / (float)4);
	terrainMaterial.AddTextureTile(loader.LoadTexture("res/Textures/Terrain/snow_mud_d.jpg"), minHeight + 4 * (maxHeight - minHeight) / (float)4);

	glfwSetInputMode(window.GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!window.IsCloseRequested())
	{
		Time::Tick();

		CameraMovement(camera, window);
		CameraLook(camera, window);

		renderer.Prepare();

		renderer.RenderTerrain(terrain, terrainMaterial);
		
		SceneEntity.Rotate( glm::vec3(0.0f, 0.05f, 0.0f));
		renderer.Render(SceneEntity, material);

		window.Update();
	}
}

// Makes camera move from WASD keys
void CameraMovement(Camera& camera, Window& window)
{
	float speed = 2 * Time::GetDeltaTime();
	if (glfwGetKey(window.GetGlfwWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 20 * Time::GetDeltaTime();
	}

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

	// Update the Camera ---------------------------------------------
	camera.Update();
}

void CameraLook(Camera& camera, Window& window)
{
	float sensitivity = 0.1f;

	double mouseX, mouseY;
	glfwGetCursorPos(window.GetGlfwWindow(), &mouseX, &mouseY);

	// Calculate the delta mouse movement
	static double lastMouseX = mouseX, lastMouseY = mouseY;
	double deltaX = mouseX - lastMouseX;
	double deltaY = lastMouseY - mouseY; // reversed since y-coordinates go from bottom to top

	// Store the current mouse position for the next frame
	lastMouseX = mouseX;
	lastMouseY = mouseY;

	// Adjust yaw and pitch based on the mouse movement
	camera.Yaw += deltaX * sensitivity;
	camera.Pitch += deltaY * sensitivity;

	// Constrain the pitch value to avoid flipping
	if (camera.Pitch > 89.0f)
		camera.Pitch = 89.0f;
	if (camera.Pitch < -89.0f)
		camera.Pitch = -89.0f;

	camera.Update();
}