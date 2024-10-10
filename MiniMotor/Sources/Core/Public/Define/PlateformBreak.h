// Copyright Shimmer Studios : All rights reserved.

#pragma once

#if _WINDOWS
	#define PLATEFORM_BREAK __nop(); __debugbreak();
#elif _LINUX
	#define PLATEFORM_BREAK __asm__("int $3");
#elif _MAC
	#define PLATEFORM_BREAK __asm__("int $3");
#endif

#define TEXT(txt, ...) std::format(txt, ##__VA_ARGS__)

#define SQUAREDTEXTURE(nbr) IVec2{0, 0}, IVec2{nbr, 0}, IVec2{nbr, nbr}, IVec2{0, nbr}
