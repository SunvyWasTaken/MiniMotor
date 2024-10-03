#include "MiniDebug/Debug.h"

#if DEBUG

bool Debug::ExeEnsureIntImpl(std::atomic<bool>& IsExecute, bool bAlways)
{
	if (bAlways || !IsExecute.load(std::memory_order_relaxed))
	{
		IsExecute.exchange(true, std::memory_order_relaxed);
		return true;
	}
	return false;
}

#endif // DEBUG