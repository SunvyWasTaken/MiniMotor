#pragma once

#include "Event.h"

namespace Sunset
{
	enum class ViewMode
	{
		Perspective,
		Ortho
	};

	class MM_API Camera
	{
	public:
		Camera();

		//virtual void Init() override;

		void Update(float deltatime);

		glm::mat4 GetViewMatrice() const;

		void ChangeRotation(const double xPos, const double yPos);

		void UpdateLocation(const glm::vec3& vec);

		glm::mat4 GetProjection() const;

	public:

		glm::vec3 m_Position;

		ViewMode viewMode;

		float yaw, pitch, roll;

		glm::vec3 m_UpVector;

		glm::vec3 m_ForwardVector;

	private:

		glm::vec2 Res;

		double lastX;

		double lastY;

		bool firstMouse;

		float MovementSpeed;
	};
}
