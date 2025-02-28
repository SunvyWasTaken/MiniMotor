#include "Camera.h"
#include "Event.h"
#include "InputComponent.h"
#include "Inputs.h"

namespace Sunset
{
	Camera::Camera()
		: m_Position({0.f, 0.f, 10.f})
		, viewMode(ViewMode::Ortho)
		, Res(1920, 1080)
		, m_UpVector({ 0.f, 1.f, 0.f })
		, m_ForwardVector({0.f, 0.f, -1.f})
		, yaw(- 90.0)
		, pitch(0.0)
		, roll(0.0)
		, lastX(0.0)
		, lastY(0.0)
		, firstMouse(true)
		, MovementSpeed(1.f)
	{
	}

	//void Camera::Init()
	//{
	//	AddComponent<InputComponent>();

	//	InputComponent& comp = GetComponent<InputComponent>();
	//	comp.Bind(87, std::bind([this](float deltatime)
	//		{
	//			UpdateLocation(glm::vec3{ 0.f, 0.f, 1.f } *deltatime * MovementSpeed);
	//		}, std::placeholders::_1));
	//	comp.Bind(83, std::bind([this](float deltatime)
	//		{
	//			UpdateLocation(glm::vec3{ 0.f, 0.f, -1.f } * deltatime * MovementSpeed);
	//		}, std::placeholders::_1));
	//	comp.Bind(68, std::bind([this](float deltatime)
	//		{
	//			UpdateLocation(glm::vec3{ 1.f, 0.f, 0.f } * deltatime * MovementSpeed);
	//		}, std::placeholders::_1));
	//	comp.Bind(65, std::bind([this](float deltatime)
	//		{
	//			UpdateLocation(glm::vec3{ -1.f, 0.f, 0.f } * deltatime * MovementSpeed);
	//		}, std::placeholders::_1));
	//	comp.Bind(69, std::bind([this](float deltatime)
	//		{
	//			UpdateLocation(glm::vec3{ 0.f, 1.f, 0.f } * deltatime * MovementSpeed);
	//		}, std::placeholders::_1));
	//	comp.Bind(81, std::bind([this](float deltatime)
	//		{
	//			UpdateLocation(glm::vec3{ 0.f, -1.f, 0.f } * deltatime * MovementSpeed);
	//		}, std::placeholders::_1));
	//}

	void Camera::Update(float deltatime)
	{
		if (Inputs::IsKeyPressed(87))
		{
			UpdateLocation(glm::vec3{ 0.f, 0.f, 1.f } * deltatime * MovementSpeed);
			LOG("Camera position : x:{}, y:{}, z:{}", m_Position.x, m_Position.y, m_Position.z);
		}
		if (Inputs::IsKeyPressed(83))
		{
			UpdateLocation(glm::vec3{ 0.f, 0.f, -1.f } * deltatime * MovementSpeed);
			LOG("Camera position : x:{}, y:{}, z:{}", m_Position.x, m_Position.y, m_Position.z);
		}
		if (Inputs::IsKeyPressed(68))
		{
			UpdateLocation(glm::vec3{ 1.f, 0.f, 0.f } * deltatime * MovementSpeed);
			LOG("Camera position : x:{}, y:{}, z:{}", m_Position.x, m_Position.y, m_Position.z);
		}
		if (Inputs::IsKeyPressed(65))
		{
			UpdateLocation(glm::vec3{ -1.f, 0.f, 0.f } * deltatime * MovementSpeed);
			LOG("Camera position : x:{}, y:{}, z:{}", m_Position.x, m_Position.y, m_Position.z);
		}
		if (Inputs::IsKeyPressed(69))
		{
			UpdateLocation(glm::vec3{ 0.f, 1.f, 0.f } *deltatime * MovementSpeed);
			LOG("Camera position : x:{}, y:{}, z:{}", m_Position.x, m_Position.y, m_Position.z);
		}
		if (Inputs::IsKeyPressed(81))
		{
			UpdateLocation(glm::vec3{ 0.f, -1.f, 0.f } *deltatime * MovementSpeed);
			LOG("Camera position : x:{}, y:{}, z:{}", m_Position.x, m_Position.y, m_Position.z);
		}
	}

	glm::mat4 Camera::GetViewMatrice() const
	{
		if (viewMode == ViewMode::Perspective)
		{
			return glm::lookAt(m_Position, m_ForwardVector, m_UpVector);
		}
		else if (viewMode == ViewMode::Ortho)
		{
			return glm::inverse(glm::translate(glm::mat4(1.f), m_Position) * glm::rotate(glm::mat4(1.f), roll, glm::vec3(0, 0, 1)));
		}
		return glm::mat4(1.f);
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

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians((float)yaw)) * cos(glm::radians((float)pitch));
		direction.y = sin(glm::radians((float)pitch));
		direction.z = sin(glm::radians((float)yaw)) * cos(glm::radians((float)pitch));
		m_ForwardVector = glm::normalize(direction);
	}

	void Camera::UpdateLocation(const glm::vec3& vec)
	{
		if (viewMode == ViewMode::Perspective)
		{
			m_Position += m_ForwardVector * vec.z;
			m_Position += m_UpVector * vec.y;
			m_Position += glm::cross(m_ForwardVector, m_UpVector) * vec.x;
		}
		else if (viewMode == ViewMode::Ortho)
		{
			roll -= vec.y;
			//LOG("Forward vec -> x:{}, y:{}, z:{}", m_ForwardVector.x, m_ForwardVector.y, m_ForwardVector.z);
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(roll), -m_ForwardVector);
			m_UpVector = glm::vec3(rotationMatrix * glm::vec4(m_UpVector, 0.0f));

			m_Position -= glm::cross(m_ForwardVector, m_UpVector) * vec.x;
			m_Position -= m_UpVector * vec.z;
		}
	}

	glm::mat4 Camera::GetProjection() const
	{
		if (viewMode == Sunset::ViewMode::Perspective)
		{
			return glm::perspective(glm::radians(45.f), Res.x / Res.y, 0.1f, (float)2e7);
		}
		else if (viewMode == Sunset::ViewMode::Ortho)
		{
			float multi = 2;
			float width = (Res.y / Res.x) * multi;
			float heigh = (1 - (Res.y / Res.x)) * multi;
			return glm::ortho(-width, width, -heigh, heigh, -1.f, 100.f);
		}
		return glm::mat4();
	}
}
