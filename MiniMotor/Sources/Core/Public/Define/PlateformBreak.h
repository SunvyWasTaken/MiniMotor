// Copyright Shimmer Studios : All rights reserved.

#pragma once

#if _WINDOWS
	#define PLATEFORM_BREAK /*__nop();*/ __debugbreak();
#elif _LINUX
	#define PLATEFORM_BREAK __asm__("int $3");
#elif _MAC
	#define PLATEFORM_BREAK __asm__("int $3");
#endif

#define TO_TEXT(txt, ...) std::format(txt, ##__VA_ARGS__)

#define SQUARECOORD(nbrStart, NbrEnd) TextureCoord{IVec2{nbrStart, nbrStart}, {NbrEnd, nbrStart}, {NbrEnd, NbrEnd}, {nbrStart, NbrEnd}}

#define SQUAREDTEXTURE(nbr) SQUARECOORD(0, nbr)
