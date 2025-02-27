#pragma once

namespace Sunset
{
	struct Light
	{
		Light() = default;

		Light(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular)
			: ambient(_ambient)
			, diffuse(_diffuse)
			, specular(_specular)
		{}

		glm::vec3 ambient, diffuse, specular;
	};

	struct Directional : public Light
	{
		Directional() = default;

		Directional(const glm::vec3& _dir, const Light& light)
			: Light(light)
			, direction(_dir)
		{ }

		glm::vec3 direction;
	};
	struct Point : public Light
	{
		Point() = default;
		Point(const glm::vec3& _pos, const float _constant, const float _linear, const float _quadratic, const Light& light)
			: Light(light)
			, position(_pos)
			, constant(_constant)
			, linear(_linear)
			, quadratic(_quadratic)
		{}
		glm::vec3 position;
		float constant, linear, quadratic;
		bool isValid = false;
	};
	struct SpotLight : public Light
	{
		SpotLight() = default;
		glm::vec3 position, direction;
		float cutOff;
	};

	using Lights = std::variant<Directional, Point, SpotLight>;
}

