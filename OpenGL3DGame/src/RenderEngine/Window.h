#pragma once
#include <GLFW/glfw3.h>

namespace OG3D
{
	class Window
	{
	public:
		Window() = delete;
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		void Update();
		void Delete();

		bool IsCloseRequested()
		{
			return glfwWindowShouldClose(m_Window);
		}

	private:
		unsigned int m_Width, m_Height;
		const char* m_Title;
		GLFWwindow* m_Window;
	};

}