#include <iostream>

#include "RenderEngine/Window.h"

int main()
{
	OG3D::Window window(800, 800, "My Game");
	window.Init();
	
	while (window.Update())
	{
		// Running the main loop
	}

	window.Delete();

	std::cout << "Press Any key to Exit!\n";
	std::cin.get();
}