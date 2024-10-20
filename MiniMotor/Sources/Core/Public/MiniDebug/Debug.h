// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "Define/ImportExportDLL.h"

#ifdef DEBUG

namespace std
{
	template <typename T>
	struct atomic;
}

struct MM_API Debug
{
	static bool ExeEnsureIntImpl(std::atomic<bool>& IsExecute, bool bAlways);
};


#define ENSURE_INTERNAL_IMPL(Expression, Always) \
	(!!(!!(Expression)) || Debug::ExeEnsureIntImpl([]()->std::atomic<bool>&{static std::atomic<bool> bExecute = false; return bExecute; }(), Always) && [](){PLATEFORM_BREAK; return false;}())

#define ensure(Expression) ENSURE_INTERNAL_IMPL(Expression, false)
#define ensureAlways(Expression) ENSURE_INTERNAL_IMPL(Expression, true)

#else // DEBUG

#define ensure(Expression)
#define ensureAlways(Expression)

#endif // DEBUG

#ifdef DO_CHECK

	#define CHECK_PERF(func) \
		{ \
			auto start = std::chrono::high_resolution_clock::now(); \
			func; \
			auto end = std::chrono::high_resolution_clock::now(); \
			std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start); \
			std::cout << "It takes : " << duration.count() << "secondes." << std::endl; \
		};

#else // DO_CHECK
	#define CHECK_PERF(func) func;
#endif // DO_CHECK
