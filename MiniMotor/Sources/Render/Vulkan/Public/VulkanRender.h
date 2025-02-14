#pragma once

#include "BasicRender.h"
namespace Sunset
{
	class MM_API VulkanRender /*: public BasicRender<VulkanRender>*/
	{
	public:
		VulkanRender(const std::string& _name, const FVec2& size);

		virtual ~VulkanRender();

		void BeginFrame();

		void Draw(const Camera* cam, const Mesh* mesh);

		void EndFrame();

		bool IsRunning() const;

		void CloseWindow();

	};
}
