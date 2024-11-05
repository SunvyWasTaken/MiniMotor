// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "Rot3.h"
#include "Vec2.h"

struct MM_EXPORT FTrans2
{
	FVec2 pos;
	FRot3 rot;
	FVec2 scale;

	FTrans2() : pos(0), rot(0), scale(1) {}
};
