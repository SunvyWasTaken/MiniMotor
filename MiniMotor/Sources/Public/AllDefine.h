// Copyright Shimmer Studios : All rights reserved.

#pragma once


#ifdef __EMSCRIPTEN__
	#define FOR_WEB
#endif

#ifdef FOR_WEB
	#define USE_VULKAN
#else
	#define RENDER_TYPE 1
	#if RENDER_TYPE == 1
	#define USE_SFML
	#elif RENDER_TYPE == 2
	#define USE_VULKAN
	#endif
#endif
