#pragma once

namespace Sunset
{
	struct Yaw {};
	struct Pitch {};
	struct Roll {};

	using RotList = Typelist<Yaw, Pitch, Roll>;

	template <typename T>
	using Rot = std::array<T, TypelistSize<RotList>::value>;

	using FRot = typename Rot<float>;

	struct Transform
	{
		Transform() : pos(0, 0, 0), scale(1, 1, 1), rotation(0) {}
		Transform(float x, float y, float z) : pos(x, y, z), scale(1, 1, 1), rotation(0) {}

		inline glm::mat4 GetModel() const 
		{
			glm::mat4 model = glm::mat4(1);
			model = glm::translate(model, pos);
			model = glm::scale(model, scale);
			model = glm::rotate(model, glm::radians(rotation[TypeIndex<Pitch, RotList>::value]), glm::vec3{1.f, 0.f, 0.f});
			model = glm::rotate(model, glm::radians(rotation[TypeIndex<Yaw, RotList>::value]), glm::vec3{0.f, 1.f, 0.f});
			model = glm::rotate(model, glm::radians(rotation[TypeIndex<Roll, RotList>::value]), glm::vec3{0.f, 0.f, 1.f});
			return model;
		}

		glm::vec3 pos;
		glm::vec3 scale;
		FRot rotation;
	};

	class MM_API TransformComponent
	{
	public:

		explicit TransformComponent(const Transform& trans);

		Transform& operator()()
		{
			return transform;
		}

		glm::vec3 GetLocation() const;

		void SetLocation(const glm::vec3& loc);

		template <typename Axis>
		void AddRotAxis(float val)
		{
			constexpr float MaxDegree = 360.f;

			float& axe = transform.rotation[TypeIndex<Axis, RotList>::value];
			axe += val;
			if (axe >= MaxDegree)
				axe -= MaxDegree;
			else if (axe <= 0.f)
				axe += MaxDegree;
		}


	private:

		Transform transform;
	};
}
