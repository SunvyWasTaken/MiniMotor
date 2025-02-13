#include "Camera.h"
#include "Event.h"
#include "Maths.h"

Camera::Camera()
	: m_Position({0.f, 0.f, 10.f})
	, viewMode(Sunset::ViewMode::Perspective)
	, Res(1920, 1080)
	, m_UpVector({ 0.f, 1.f, 0.f })
	, m_ForwardVector({0.f, 0.f, -1.f})
	, m_Rotation({-90.0, 0.0, 0.0})
	, lastX(0.0)
	, lastY(0.0)
	, firstMouse(true)
{
}

FMat4 Camera::GetViewMatrice() const
{
	LookAt<FMat4> lookAt;
	return lookAt(m_Position, m_ForwardVector, m_UpVector);
}

void Camera::ChangeRotation(const double xPos, const double yPos)
{
	if (firstMouse)
	{
		lastX = (float)xPos;
		lastY = (float)yPos;
		firstMouse = false;
	}

	float xoffset = (float)(xPos - lastX);
	float yoffset = (float)(lastY - yPos); // reversed since y-coordinates range from bottom to top
	lastX = (float)xPos;
	lastY = (float)yPos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_Rotation.yaw += xoffset;
	m_Rotation.pitch += yoffset;

	if (m_Rotation.pitch > 89.0f)
		m_Rotation.pitch = 89.0f;
	if (m_Rotation.pitch < -89.0f)
		m_Rotation.pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians((float)m_Rotation.yaw)) * cos(glm::radians((float)m_Rotation.pitch));
	direction.y = sin(glm::radians((float)m_Rotation.pitch));
	direction.z = sin(glm::radians((float)m_Rotation.yaw)) * cos(glm::radians((float)m_Rotation.pitch));
	m_ForwardVector = glm::normalize(direction);
}

void Camera::UpdateLocation(const FVec3& vec)
{
	Cross<FVec3> cross;
	m_Position += m_ForwardVector * vec.z;
	m_Position += m_UpVector * vec.y;
	m_Position += cross(m_ForwardVector, m_UpVector) * vec.x;
}

FMat4 Camera::GetProjection() const
{
	if (viewMode == Sunset::ViewMode::Perspective)
	{
		Perspective<FMat4> perspective;
		Radian<float> radian;
		return perspective(radian(45.f), Res.x / Res.y, 0.1f, 200.f);
	}
	else if (viewMode == Sunset::ViewMode::Ortho)
	{
		float multi = 2;
		float width = (Res.y / Res.x) * multi;
		float heigh = (1 - (Res.y / Res.x)) * multi;
		return glm::ortho(-width, width, -heigh, heigh, -1.f, 100.f);
	}
	return FMat4();
}
