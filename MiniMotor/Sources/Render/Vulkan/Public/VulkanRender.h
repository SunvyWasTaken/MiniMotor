#pragma once

#include "BasicRender.h"
#include "Lights.h"

namespace Sunset
{
	class MM_API VulkanRender : public BasicRender<VulkanRender>
	{
	public:
		VulkanRender(const std::string& _name, const FVec2& size);

		virtual ~VulkanRender() override;

		void BeginFrame();

		void DrawLight(const Lights* light);

		void Draw(const Camera* cam, const Mesh* mesh, const Transform& trans);

		void EndFrame();

		bool IsRunning();

		void CloseWindow();

	};
}
