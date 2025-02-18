#pragma once

#include "Maths.h"

#include <variant>

namespace Sunset
{
	struct Light
	{
		Light() = default;

		Light(const FVec3& _ambient, const FVec3& _diffuse, const FVec3& _specular)
			: ambient(_ambient)
			, diffuse(_diffuse)
			, specular(_specular)
		{}

		FVec3 ambient, diffuse, specular;
	};

	struct Directional : public Light
	{
		Directional() = default;

		Directional(const FVec3& _dir, const Light& light)
			: Light(light)
			, direction(_dir)
		{ }

		FVec3 direction;
	};
	struct Point : public Light
	{
		Point() = default;
		Point(const FVec3& _pos, const float _constant, const float _linear, const float _quadratic, const Light& light)
			: Light(light)
			, position(_pos)
			, constant(_constant)
			, linear(_linear)
			, quadratic(_quadratic)
		{}
		FVec3 position;
		float constant, linear, quadratic;
		bool isValid = false;
	};
	struct SpotLight : public Light
	{
		SpotLight() = default;
		FVec3 position, direction;
		float cutOff;
	};

	using Lights = std::variant<Directional, Point, SpotLight>;
}

