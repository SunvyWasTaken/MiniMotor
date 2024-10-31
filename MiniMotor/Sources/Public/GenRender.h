// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "AllDefine.h"

#ifdef USE_SFML
	#include "SFMLRender.h"
	using CurrentRender = SFMLRender;
#endif
#ifdef USE_VULKAN
	#include "VulkanRender.h"
	using CurrentRender = VulkanRender;
#endif
