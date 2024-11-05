// Copyright Shimmer Studios : All rights reserved.

#pragma once

struct MM_API Vertex2D
{
	FVec2 position;
	FColor color;
	FVec2 texCoords;
};

struct MM_API Vertex3D
{
	FVec3 position;
	FVec2 texCoords;
	FVec3 normal;
	FColor color;
};
