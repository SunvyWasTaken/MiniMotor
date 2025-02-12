#pragma once

#include "Maths.h"

class Camera
{
public:
	Camera();

	FMat4 GetViewMatrice() const;

	void ChangeRotation(const double xPos, const double yPos);

	void UpdateLocation(const FVec3& vec);

public:

	FVec3 m_Position;

private:

	FVec3 m_UpVector;

	FVec3 m_ForwardVector;

	DRot m_Rotation;

	double lastX;

	double lastY;

	bool firstMouse;
};
