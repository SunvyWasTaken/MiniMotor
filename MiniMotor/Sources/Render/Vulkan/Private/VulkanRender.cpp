#include "VulkanRender.h"

namespace Sunset
{

	VulkanRender::VulkanRender(const std::string& _name, const FVec2& size)
		: BasicRender<VulkanRender>(_name, size)
	{

	}

	VulkanRender::~VulkanRender()
	{

	}

	void VulkanRender::BeginFrame()
	{

	}

	void VulkanRender::DrawLight(const Lights* light)
	{

	}

	void VulkanRender::Draw(const Camera* cam, const Mesh* mesh, const Transform& trans)
	{

	}

	void VulkanRender::EndFrame()
	{

	}

	bool VulkanRender::IsRunning()
	{
		return false;
	}

	void VulkanRender::CloseWindow()
	{

	}

}

