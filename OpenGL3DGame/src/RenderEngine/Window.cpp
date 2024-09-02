#include "Window.h"

namespace OG3D
{
	Window::Window(unsigned int width, unsigned int height, const char* title)
		:m_Width(width), m_Height(height), m_Title(title)
	{
	}

	Window::~Window()
	{
		Delete();
	}

	bool Window::Init()
	{
		if (!glfwInit()) return false;
		
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) return false;
		
		glfwMakeContextCurrent(m_Window);

		return true;
	}

	bool Window::Update()
	{
		if (glfwWindowShouldClose(m_Window)) return false;

		glClearColor(.1f, .1f, .1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		return true;
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