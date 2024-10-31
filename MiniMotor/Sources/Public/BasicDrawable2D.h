// Copyright Shimmer Studios : All rights reserved.

#pragma once

class Entity;

class MM_API BasicDrawable2D
{
public:
	explicit BasicDrawable2D(const FTrans2& trans);
	virtual ~BasicDrawable2D();

	FTrans2 transform;
};
