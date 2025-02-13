#include "VulkanRender.h"

VulkanRender::VulkanRender(const std::string& _name, const FVec2& size)
	//: BasicRender<VulkanRender>(_name, size)
{
}

VulkanRender::~VulkanRender()
{
}

void VulkanRender::BeginFrame()
{
}

void VulkanRender::Draw(const Camera* cam, const Mesh* mesh)
{
}

void VulkanRender::EndFrame()
{
}

bool VulkanRender::IsRunning() const
{
	return false;
}

void VulkanRender::CloseWindow()
{
}
