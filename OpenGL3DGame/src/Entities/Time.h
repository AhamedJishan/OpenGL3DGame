#include <GLFW/glfw3.h>

namespace OG3D
{
	class Time
	{
	public:

		static Time& Get()
		{
			return instance;
		}

		static float GetDeltaTime()
		{
			return Get().deltaTime;
		}

		static void Tick()
		{
			Time& time = Get();
			time.m_CurrentFrame = glfwGetTime();
			time.deltaTime = time.m_CurrentFrame - time.m_LastFrame;
			time.m_LastFrame = time.m_CurrentFrame;
		}

	private:
		static Time instance;
		float deltaTime;
		float m_CurrentFrame;
		float m_LastFrame;

	private:
		Time()
		{
			m_CurrentFrame = 0.0f;
			m_LastFrame = 0.0f;
		}

		Time(const Time&) = delete;
	};

	Time Time::instance;
}