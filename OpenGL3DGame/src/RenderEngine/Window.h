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

		bool Init();
		bool Update();
		void Delete();

	private:
		unsigned int m_Width, m_Height;
		const char* m_Title;
		GLFWwindow* m_Window;
	};

}