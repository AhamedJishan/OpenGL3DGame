#pragma once
#define GLFW_INCLUDE_NONE
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

		float GetAspectRatio() { return (float)m_Width / (float)m_Height; }

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