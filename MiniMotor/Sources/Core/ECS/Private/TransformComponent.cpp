#include "TransformComponent.h"

namespace Sunset
{
	TransformComponent::TransformComponent(const Transform& trans)
		: transform(trans)
	{
	}

	glm::vec3 TransformComponent::GetLocation() const
	{
		return transform.pos;
	}

	void TransformComponent::SetLocation(const glm::vec3& loc)
	{
		transform.pos = loc;
	}

}