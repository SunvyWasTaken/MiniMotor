#pragma once

#ifdef MiniMotor_EXPORTS
#define MM_API __declspec(dllexport)
#define MM_EXPORT MM_API
#else
#define MM_API __declspec(dllimport)
#define MM_EXPORT
#endif // MiniMotor_EXPORTS
