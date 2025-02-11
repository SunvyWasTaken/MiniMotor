#pragma once

#include "Maths.h"

class Camera
{
public:
	Camera();

	FMat4 GetViewMatrice() const;

private:
	FVec3 m_Position;
	FVec3 m_UpVector;
	FVec3 m_ForwardVector;
	DRot m_Rotation;
};
