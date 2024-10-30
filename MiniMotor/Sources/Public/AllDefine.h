// Copyright Shimmer Studios : All rights reserved.

#pragma once

//#define RENDER_TYPE 2

#ifdef __EMSCRIPTEN__
	#define FOR_WEB
#endif

#ifdef RENDER_TYPE
	#if RENDER_TYPE == 1
		#define USE_SFML
	#elif RENDER_TYPE == 2
		#define USE_VULKAN
	#endif
#else
	#ifdef FOR_WEB
		#define USE_VULKAN
	#else
		#define USE_SFML
	#endif
#endif

