#include <iostream>

#include "Window.h"
#include <glad/glad.h>

namespace OG3D
{
	Window::Window(unsigned int width, unsigned int height, const char* title)
		:m_Width(width), m_Height(height), m_Title(title)
	{
		if (!glfwInit()) std::cerr << "Failed to initialise GLFW\n";

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) std::cerr << "Failed to create Window\n";

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
		}
	}

	Window::~Window()
	{
		Delete();
	}

	void Window::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::Delete()
	{
		if (m_Window)
		{
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}
		glfwTerminate();
	}
}