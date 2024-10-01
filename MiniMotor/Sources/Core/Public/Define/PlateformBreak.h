
#pragma once

#if _WINDOWS
	#define PLATEFORM_BREAK __nop(); __debugbreak();
#elif _LINUX
	#define PLATEFORM_BREAK __asm__("int $3");
#elif _MAC
	#define PLATEFORM_BREAK __asm__("int $3");
#endif
