#pragma once

#include "Entity.h"
#include "Event.h"

namespace Sunset
{
	enum class ViewMode
	{
		Perspective,
		Ortho
	};

	class MM_API Camera : public Entity
	{
	public:
		Camera();

		virtual void Init() override;

		virtual void Update(float deltatime) override;

		glm::mat4 GetViewMatrice() const;

		void ChangeRotation(const double xPos, const double yPos);

		void UpdateLocation(const glm::vec3& vec);

		glm::mat4 GetProjection() const;

	public:

		glm::vec3 m_Position;

		ViewMode viewMode;

	private:

		glm::vec2 Res;

		glm::vec3 m_UpVector;

		glm::vec3 m_ForwardVector;

		glm::vec3 m_Rotation;

		double lastX;

		double lastY;

		bool firstMouse;

		float MovementSpeed;
	};
}
