// Copyright Shimmer Studios : All rights reserved.

#pragma once

#ifdef USE_SFML
	#include "SFMLRender.h"
	using CurrentRender = SFMLRender;
#endif
#ifdef USE_VULKAN
	#include "VulkanRender.h"
	using CurrentRender = VulkanRender;
#endif
