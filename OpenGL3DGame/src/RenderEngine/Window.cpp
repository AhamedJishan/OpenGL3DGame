#include "Window.h"
#include <iostream>

namespace OG3D
{
	Window::Window(unsigned int width, unsigned int height, const char* title)
		:m_Width(width), m_Height(height), m_Title(title)
	{
		if (!glfwInit()) std::cerr << "Failed to initialise GLFW\n";

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) std::cerr << "Failed to create Window\n";

		glfwMakeContextCurrent(m_Window);
	}

	Window::~Window()
	{
		Delete();
	}

	void Window::Update()
	{

		glClearColor(.1f, .1f, .1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
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