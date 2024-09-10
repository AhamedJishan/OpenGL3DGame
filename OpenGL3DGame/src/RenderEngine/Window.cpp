#include <iostream>

#include <glad/glad.h>

#include "Window.h"

namespace OG3D
{
	// Callback function to handle window resize
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// Set the new viewport
		glViewport(0, 0, width, height);
	}

	Window::Window(unsigned int width, unsigned int height, const char* title)
		:m_Width(width), m_Height(height), m_Title(title)
	{
		if (!glfwInit()) std::cerr << "Failed to initialise GLFW\n";

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) std::cerr << "Failed to create Window\n";

		glfwMakeContextCurrent(m_Window);


		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
		}

		// Register the framebuffer size callback function
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
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