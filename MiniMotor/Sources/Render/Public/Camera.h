#pragma once

#include "Maths.h"

namespace Sunset
{
	enum class ViewMode
	{
		Perspective,
		Ortho
	};
}

class MM_API Camera
{
public:
	Camera();

	FMat4 GetViewMatrice() const;

	void ChangeRotation(const double xPos, const double yPos);

	void UpdateLocation(const FVec3& vec);

	FMat4 GetProjection() const;

public:

	FVec3 m_Position;

	Sunset::ViewMode viewMode;

private:

	FVec2 Res;

	FVec3 m_UpVector;

	FVec3 m_ForwardVector;

	DRot m_Rotation;

	double lastX;

	double lastY;

	bool firstMouse;
};
