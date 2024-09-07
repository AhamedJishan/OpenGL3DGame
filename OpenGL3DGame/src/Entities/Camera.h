#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace OG3D
{
	class Camera
	{
	public:
		glm::vec3 WorldUp;
		glm::vec3 Position;
		glm::vec3 Forward;
		glm::vec3 Right;
		glm::vec3 Up;

		float Yaw;
		float Pitch;


	public:
		Camera (glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
		{
			WorldUp = up;
			Position = position;
			Forward = glm::vec3(0.0f, 0.0f, -1.0f);
			Right = glm::normalize(glm::cross(Forward, Up));
			Yaw = -90.0f;
			Pitch = 0.0f;
			UpdateCamera();
		}
		~Camera() = default;

		glm::mat4& GetViewMatrix()
		{
			return glm::lookAt(Position, Position + Forward, Up);
		}

	private:
		void UpdateCamera()
		{
			glm::vec3 direction;
			direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			direction.y = sin(glm::radians(Pitch));
			direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

			Forward = glm::normalize(direction);
			Right = glm::normalize(glm::cross(direction, WorldUp));
			Up = glm::normalize(glm::cross(Right, Forward));
		}
	};
}