// Copyright Shimmer Studios : All rights reserved.

#include "ECS/Components/TagComponent.h"

TagComponent::TagComponent(const std::string& name)
	: tag(name.empty() ? "Unamed Object" : name)
{
}
