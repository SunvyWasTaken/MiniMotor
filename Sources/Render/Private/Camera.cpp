#include "Camera.h"

Camera::Camera()
	: m_Position({0.f, 0.f, 10.f})
	, m_UpVector({ 0.f, 1.f, 0.f })
	, m_ForwardVector({0.f, 0.f, -1.f})
	, m_Rotation({-90.0, 0.0, 0.0})
{
}

FMat4 Camera::GetViewMatrice() const
{
	LookAt<FMat4> lookAt;
	return lookAt(m_Position, m_ForwardVector, m_UpVector);
}
