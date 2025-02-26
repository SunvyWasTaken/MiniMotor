#pragma once

#include "BasicRender.h"
#include "Lights.h"

namespace Sunset
{
	class MM_API VulkanRender : public BasicRender<VulkanRender>
	{
	public:
		void SwapBuffers();

	};
}
