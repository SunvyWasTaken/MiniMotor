// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "Rot3.h"
#include "Vec2.h"

template <typename T>
struct MM_EXPORT Trans2
{
	Vec2<T> pos;
	Rot3<T> rot;
	Vec2<T> scale;

	Trans2() : pos(0), rot(0), scale(50) {}

	Trans2(Vec2<T> _pos) : pos(_pos), rot(), scale(1) {}

	Trans2(Vec2<T> _pos, Rot3<T> _rot) : pos(_pos), rot(_rot), scale(1) {}

	Trans2(Vec2<T> _pos, Rot3<T> _rot, Vec2<T> _scale) : pos(_pos), rot(_rot), scale(_scale) {}

	bool Collide(const Trans2<T>& op) const
	{
		return ((pos.x >= op.pos.x && pos.x <= op.pos.x + op.scale.x) 
				|| (pos.x + scale.x >= op.pos.x && pos.x + scale.x <= op.pos.x + op.scale.x))
				&& ((pos.y >= op.pos.y && pos.y <= op.pos.y + op.scale.y)
				|| (pos.y + scale.y >= op.pos.y && pos.y + scale.y <= op.pos.y + op.scale.y));
	}

};

using FTrans2 = Trans2<double>;
