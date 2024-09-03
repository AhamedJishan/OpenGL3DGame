#include <iostream>

#include "RenderEngine/Window.h"

int main()
{
	OG3D::Window window(1920, 1080, "My Game");
	
	while (!window.IsCloseRequested())
	{
		// Running the main loop
		window.Update();
	}

	window.Delete();
}