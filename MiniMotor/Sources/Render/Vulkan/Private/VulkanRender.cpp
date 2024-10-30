// Copyright Shimmer Studios : All rights reserved.

#include "VulkanRender.h"
#include "Geometry/Vertex2D.h"

// This allow glfw to include it's requirement for vulkan
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define CREATE_INSTANCE(func, error, success, ...) if (func != VK_SUCCESS) { throw std::runtime_error(error); } else { LOG("### " << TO_TEXT(success, ##__VA_ARGS__) << " ###") }

#ifndef NDEBUG
const char* vulkanFormat[]{"VK_FORMAT_UNDEFINED",
"VK_FORMAT_R4G4_UNORM_PACK8",
"VK_FORMAT_R4G4B4A4_UNORM_PACK16",
"VK_FORMAT_B4G4R4A4_UNORM_PACK16",
"VK_FORMAT_R5G6B5_UNORM_PACK16",
"VK_FORMAT_B5G6R5_UNORM_PACK16",
"VK_FORMAT_R5G5B5A1_UNORM_PACK16",
"VK_FORMAT_B5G5R5A1_UNORM_PACK16",
"VK_FORMAT_A1R5G5B5_UNORM_PACK16",
"VK_FORMAT_R8_UNORM",
"VK_FORMAT_R8_SNORM",
"VK_FORMAT_R8_USCALED",
"VK_FORMAT_R8_SSCALED",
"VK_FORMAT_R8_UINT",
"VK_FORMAT_R8_SINT",
"VK_FORMAT_R8_SRGB",
"VK_FORMAT_R8G8_UNORM",
"VK_FORMAT_R8G8_SNORM",
"VK_FORMAT_R8G8_USCALED",
"VK_FORMAT_R8G8_SSCALED",
"VK_FORMAT_R8G8_UINT",
"VK_FORMAT_R8G8_SINT",
"VK_FORMAT_R8G8_SRGB",
"VK_FORMAT_R8G8B8_UNORM",
"VK_FORMAT_R8G8B8_SNORM",
"VK_FORMAT_R8G8B8_USCALED",
"VK_FORMAT_R8G8B8_SSCALED",
"VK_FORMAT_R8G8B8_UINT",
"VK_FORMAT_R8G8B8_SINT",
"VK_FORMAT_R8G8B8_SRGB",
"VK_FORMAT_B8G8R8_UNORM",
"VK_FORMAT_B8G8R8_SNORM",
"VK_FORMAT_B8G8R8_USCALED",
"VK_FORMAT_B8G8R8_SSCALED",
"VK_FORMAT_B8G8R8_UINT",
"VK_FORMAT_B8G8R8_SINT",
"VK_FORMAT_B8G8R8_SRGB",
"VK_FORMAT_R8G8B8A8_UNORM",
"VK_FORMAT_R8G8B8A8_SNORM",
"VK_FORMAT_R8G8B8A8_USCALED",
"VK_FORMAT_R8G8B8A8_SSCALED",
"VK_FORMAT_R8G8B8A8_UINT",
"VK_FORMAT_R8G8B8A8_SINT",
"VK_FORMAT_R8G8B8A8_SRGB",
"VK_FORMAT_B8G8R8A8_UNORM",
"VK_FORMAT_B8G8R8A8_SNORM",
"VK_FORMAT_B8G8R8A8_USCALED",
"VK_FORMAT_B8G8R8A8_SSCALED",
"VK_FORMAT_B8G8R8A8_UINT",
"VK_FORMAT_B8G8R8A8_SINT",
"VK_FORMAT_B8G8R8A8_SRGB",
"VK_FORMAT_A8B8G8R8_UNORM_PACK32",
"VK_FORMAT_A8B8G8R8_SNORM_PACK32",
"VK_FORMAT_A8B8G8R8_USCALED_PACK32",
"VK_FORMAT_A8B8G8R8_SSCALED_PACK32",
"VK_FORMAT_A8B8G8R8_UINT_PACK32",
"VK_FORMAT_A8B8G8R8_SINT_PACK32",
"VK_FORMAT_A8B8G8R8_SRGB_PACK32",
"VK_FORMAT_A2R10G10B10_UNORM_PACK32",
"VK_FORMAT_A2R10G10B10_SNORM_PACK32",
"VK_FORMAT_A2R10G10B10_USCALED_PACK32",
"VK_FORMAT_A2R10G10B10_SSCALED_PACK32",
"VK_FORMAT_A2R10G10B10_UINT_PACK32",
"VK_FORMAT_A2R10G10B10_SINT_PACK32",
"VK_FORMAT_A2B10G10R10_UNORM_PACK32",
"VK_FORMAT_A2B10G10R10_SNORM_PACK32",
"VK_FORMAT_A2B10G10R10_USCALED_PACK32",
"VK_FORMAT_A2B10G10R10_SSCALED_PACK32",
"VK_FORMAT_A2B10G10R10_UINT_PACK32",
"VK_FORMAT_A2B10G10R10_SINT_PACK32",
"VK_FORMAT_R16_UNORM",
"VK_FORMAT_R16_SNORM",
"VK_FORMAT_R16_USCALED",
"VK_FORMAT_R16_SSCALED",
"VK_FORMAT_R16_UINT",
"VK_FORMAT_R16_SINT",
"VK_FORMAT_R16_SFLOAT",
"VK_FORMAT_R16G16_UNORM",
"VK_FORMAT_R16G16_SNORM",
"VK_FORMAT_R16G16_USCALED",
"VK_FORMAT_R16G16_SSCALED",
"VK_FORMAT_R16G16_UINT",
"VK_FORMAT_R16G16_SINT",
"VK_FORMAT_R16G16_SFLOAT",
"VK_FORMAT_R16G16B16_UNORM",
"VK_FORMAT_R16G16B16_SNORM",
"VK_FORMAT_R16G16B16_USCALED",
"VK_FORMAT_R16G16B16_SSCALED",
"VK_FORMAT_R16G16B16_UINT",
"VK_FORMAT_R16G16B16_SINT",
"VK_FORMAT_R16G16B16_SFLOAT",
"VK_FORMAT_R16G16B16A16_UNORM",
"VK_FORMAT_R16G16B16A16_SNORM",
"VK_FORMAT_R16G16B16A16_USCALED",
"VK_FORMAT_R16G16B16A16_SSCALED",
"VK_FORMAT_R16G16B16A16_UINT",
"VK_FORMAT_R16G16B16A16_SINT",
"VK_FORMAT_R16G16B16A16_SFLOAT",
"VK_FORMAT_R32_UINT",
"VK_FORMAT_R32_SINT",
"VK_FORMAT_R32_SFLOAT",
"VK_FORMAT_R32G32_UINT",
"VK_FORMAT_R32G32_SINT",
"VK_FORMAT_R32G32_SFLOAT",
"VK_FORMAT_R32G32B32_UINT",
"VK_FORMAT_R32G32B32_SINT",
"VK_FORMAT_R32G32B32_SFLOAT",
"VK_FORMAT_R32G32B32A32_UINT",
"VK_FORMAT_R32G32B32A32_SINT",
"VK_FORMAT_R32G32B32A32_SFLOAT",
"VK_FORMAT_R64_UINT",
"VK_FORMAT_R64_SINT",
"VK_FORMAT_R64_SFLOAT",
"VK_FORMAT_R64G64_UINT",
"VK_FORMAT_R64G64_SINT",
"VK_FORMAT_R64G64_SFLOAT",
"VK_FORMAT_R64G64B64_UINT",
"VK_FORMAT_R64G64B64_SINT",
"VK_FORMAT_R64G64B64_SFLOAT",
"VK_FORMAT_R64G64B64A64_UINT",
"VK_FORMAT_R64G64B64A64_SINT",
"VK_FORMAT_R64G64B64A64_SFLOAT",
"VK_FORMAT_B10G11R11_UFLOAT_PACK32",
"VK_FORMAT_E5B9G9R9_UFLOAT_PACK32",
"VK_FORMAT_D16_UNORM",
"VK_FORMAT_X8_D24_UNORM_PACK32",
"VK_FORMAT_D32_SFLOAT",
"VK_FORMAT_S8_UINT",
"VK_FORMAT_D16_UNORM_S8_UINT",
"VK_FORMAT_D24_UNORM_S8_UINT",
"VK_FORMAT_D32_SFLOAT_S8_UINT",
"VK_FORMAT_BC1_RGB_UNORM_BLOCK",
"VK_FORMAT_BC1_RGB_SRGB_BLOCK",
"VK_FORMAT_BC1_RGBA_UNORM_BLOCK",
"VK_FORMAT_BC1_RGBA_SRGB_BLOCK",
"VK_FORMAT_BC2_UNORM_BLOCK",
"VK_FORMAT_BC2_SRGB_BLOCK",
"VK_FORMAT_BC3_UNORM_BLOCK",
"VK_FORMAT_BC3_SRGB_BLOCK",
"VK_FORMAT_BC4_UNORM_BLOCK",
"VK_FORMAT_BC4_SNORM_BLOCK",
"VK_FORMAT_BC5_UNORM_BLOCK",
"VK_FORMAT_BC5_SNORM_BLOCK",
"VK_FORMAT_BC6H_UFLOAT_BLOCK",
"VK_FORMAT_BC6H_SFLOAT_BLOCK",
"VK_FORMAT_BC7_UNORM_BLOCK",
"VK_FORMAT_BC7_SRGB_BLOCK",
"VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK",
"VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK",
"VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK",
"VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK",
"VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK",
"VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK",
"VK_FORMAT_EAC_R11_UNORM_BLOCK",
"VK_FORMAT_EAC_R11_SNORM_BLOCK",
"VK_FORMAT_EAC_R11G11_UNORM_BLOCK",
"VK_FORMAT_EAC_R11G11_SNORM_BLOCK",
"VK_FORMAT_ASTC_4x4_UNORM_BLOCK",
"VK_FORMAT_ASTC_4x4_SRGB_BLOCK",
"VK_FORMAT_ASTC_5x4_UNORM_BLOCK",
"VK_FORMAT_ASTC_5x4_SRGB_BLOCK",
"VK_FORMAT_ASTC_5x5_UNORM_BLOCK",
"VK_FORMAT_ASTC_5x5_SRGB_BLOCK",
"VK_FORMAT_ASTC_6x5_UNORM_BLOCK",
"VK_FORMAT_ASTC_6x5_SRGB_BLOCK",
"VK_FORMAT_ASTC_6x6_UNORM_BLOCK",
"VK_FORMAT_ASTC_6x6_SRGB_BLOCK",
"VK_FORMAT_ASTC_8x5_UNORM_BLOCK",
"VK_FORMAT_ASTC_8x5_SRGB_BLOCK",
"VK_FORMAT_ASTC_8x6_UNORM_BLOCK",
"VK_FORMAT_ASTC_8x6_SRGB_BLOCK",
"VK_FORMAT_ASTC_8x8_UNORM_BLOCK",
"VK_FORMAT_ASTC_8x8_SRGB_BLOCK",
"VK_FORMAT_ASTC_10x5_UNORM_BLOCK",
"VK_FORMAT_ASTC_10x5_SRGB_BLOCK",
"VK_FORMAT_ASTC_10x6_UNORM_BLOCK",
"VK_FORMAT_ASTC_10x6_SRGB_BLOCK",
"VK_FORMAT_ASTC_10x8_UNORM_BLOCK",
"VK_FORMAT_ASTC_10x8_SRGB_BLOCK",
"VK_FORMAT_ASTC_10x10_UNORM_BLOCK",
"VK_FORMAT_ASTC_10x10_SRGB_BLOCK",
"VK_FORMAT_ASTC_12x10_UNORM_BLOCK",
"VK_FORMAT_ASTC_12x10_SRGB_BLOCK",
"VK_FORMAT_ASTC_12x12_UNORM_BLOCK",
"VK_FORMAT_ASTC_12x12_SRGB_BLOCK", };
const char* vulkanPresMode[]{"VK_PRESENT_MODE_IMMEDIATE_KHR",
"VK_PRESENT_MODE_MAILBOX_KHR",
"VK_PRESENT_MODE_FIFO_KHR",
"VK_PRESENT_MODE_FIFO_RELAXED_KHR"};
#endif // !NDEBUG

namespace
{
	/************************************************************************/
	/* ObjectTest															*/
	/************************************************************************/

	struct Vertice
	{
		glm::vec2 pos;
		glm::vec3 color;
	};

	const std::vector<Vertice> vertices = {
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
	};

	VkVertexInputBindingDescription GetVertexBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertice);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	using VertexAttributDescriptions = std::array<VkVertexInputAttributeDescription, 2>;

	VertexAttributDescriptions GetVertexAttributeDescriptions()
	{
		VertexAttributDescriptions attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertice, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertice, color);

		return attributeDescriptions;
	}

	/************************************************************************/
	/* Utils																*/
	/************************************************************************/

	MAKE_STATE(GraphicFamily)
	MAKE_STATE(PresentFamily)

	using QueueFamily = Typelist<GraphicFamily, PresentFamily>;

	template <typename QueueType>
	class QueueFamilyIndices_T
	{
	public:
		template <typename IndiceType>
		const QueueType& Get() const
		{
			static_assert(IsTypeInList<IndiceType, QueueFamily>::value, "Indice type isn't in the list");
			return Indices[GetTypelistIndex<IndiceType, QueueFamily>::value].value();
		}

		template <typename IndiceType>
		void Set(const QueueType& val)
		{
			static_assert(IsTypeInList<IndiceType, QueueFamily>::value, "Indice type isn't in the list");
			Indices[GetTypelistIndex<IndiceType, QueueFamily>::value] = val;
		}

		auto begin() const
		{
			return Indices.begin();
		}

		auto end() const
		{
			return Indices.end();
		}

		operator bool() const
		{
			for (auto& indice : Indices)
			{
				if (!indice.has_value())
				{
					return false;
				}
			}
			return true;
		}

		size_t size() const
		{
			return Indices.size();
		}

		bool Identical() const
		{
			if (!this)
				return false;

			auto indiceTm = Indices[0];
			for (size_t i = 1; i < Indices.size(); ++i)
			{
				if (indiceTm != Indices[i])
				{
					return false;
				}
			}
			return true;
		}

	private:
		std::array<std::optional<QueueType>, GetSizelist<QueueFamily>::value> Indices;
	};

	using QueueFamilyIndices = QueueFamilyIndices_T<uint32_t>;

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct UniformBufferObject
	{
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	/************************************************************************/
	/* Parameters															*/
	/************************************************************************/

	const char* AppName = "Vulkan Test";

	const char* EngineName = "MiniMotor";

	GLFWwindow* window = nullptr;
	const uint32_t m_width = 800;
	const uint32_t m_height = 600;

	const int MAX_FRAMES_IN_FLIGHT = 2;

	const auto startTime = std::chrono::high_resolution_clock::now();

	// A instance is a connection between the app and VulkLib
	VkInstance m_instance;

	const std::vector<const char*> m_validationLayers = {
	"VK_LAYER_KHRONOS_validation"
	};

#ifndef NDEBUG
	constexpr bool enableValidationLayers = true;
#else
	constexpr bool enableValidationLayers = false;
#endif // !NDEBUG


	// It's the device on the computer
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;

	// Instance which going to communicate with the device
	VkDevice m_device;

	//
	VkQueue m_graphicQueue;

	// In case the device doesn't have the same graphic and present queue
	VkQueue m_presentQueue;

	// It's the instance of the window for vulkan cuz abstraction
	VkSurfaceKHR m_surface;

	const std::vector<const char*> m_deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	VkSwapchainKHR m_swapChain;

	std::vector<VkImage> m_swapChainImages;

	VkFormat m_swapChainImageFormat;

	VkExtent2D m_swapChainExtent;

	std::vector<VkImageView> m_swapchainImageViews;

	VkPipelineLayout m_pipelineLayout;

	VkRenderPass m_renderPass;

	VkDescriptorSetLayout m_descriptorSetLayout;

	VkPipeline m_graphicsPipeline;

	std::vector<VkFramebuffer> m_swapChainFramebuffers;

	VkCommandPool m_commandPool;

	std::vector<VkCommandBuffer> m_commandBuffers;

	std::vector<VkSemaphore> m_imageAvailableSemaphore;

	std::vector<VkSemaphore> m_renderFinishedSemaphore;

	std::vector<VkFence> m_inFlightFences;

	// Liste des images qui sont en vol pour évité de passer dessus
	std::vector<VkFence> m_imageInFlight;

	size_t m_currentFrame = 0;

	// Check si il y a un redimensionnement
	bool m_framebufferResized = false;

	VkBuffer m_vertexBuffer;

	VkDeviceMemory m_vertexBufferMemory;

	VkBuffer m_indexBuffer;

	VkDeviceMemory m_indexBufferMemory;

	std::vector<VkBuffer> m_uniformBuffers;

	std::vector<VkDeviceMemory> m_uniformBuffersMemory;

	VkDescriptorPool m_descriptorPool;

	std::vector<VkDescriptorSet> m_descriptorSets;

	VkImage m_textureImage;

	VkDeviceMemory m_textureImageMemory;

	/************************************************************************/
	/* FuncUtils															*/
	/************************************************************************/

	VkCommandBuffer BeginSingleTimeCommands()
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_commandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(m_device, &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		return commandBuffer;
	}

	void EndSingleTimeCommands(VkCommandBuffer commandBuffer)
	{
		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(m_graphicQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_graphicQueue);

		vkFreeCommandBuffers(m_device, m_commandPool, 1, &commandBuffer);
	}

	bool CheckValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : m_validationLayers)
		{
			bool layerFound = false;
			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}
			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		LOG(TO_TEXT("  - Number of queue family : {}", queueFamilyCount));
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{

				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);
				if (presentSupport)
				{
					indices.Set<PresentFamily>(i);
				}

				indices.Set<GraphicFamily>(i);
				if (indices)
				{
					break;
				}
			}
			++i;
		}
		return indices;
	}

	bool CheckDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
		std::vector<std::string> RequiredExtensions;
		for (auto extension : m_deviceExtensions)
		{
			RequiredExtensions.emplace_back(extension);
		}
		for (const auto& extension : availableExtensions)
		{
			std::erase_if(RequiredExtensions, [&](const std::string& str) { return str == extension.extensionName; });
		}
		return RequiredExtensions.empty();
	}
	
	// Step : Swapchain
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device)
	{
		LOG("Swap chain :")
		SwapChainSupportDetails details;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.capabilities);
		LOG(TO_TEXT("Capacity, min : {}, max : {} \nCurrent extent : w : {}, h : {}", details.capabilities.minImageCount, details.capabilities.maxImageCount, details.capabilities.currentExtent.width, details.capabilities.currentExtent.height))
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.formats.data());
		}
	#ifndef NDEBUG
		LOG("Format available :")
		for (size_t i = 0; i < formatCount; ++i)
		{
			LOG(TO_TEXT(" - {}", vulkanFormat[details.formats[i].format]))
		}
	#endif // !NDEBUG


		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.presentModes.data());
		}
	#ifndef NDEBUG
		LOG("Presenstation Mode :")
		for (size_t i = 0; i < presentModeCount; ++i)
		{
			LOG(TO_TEXT(" - {}", vulkanPresMode[details.presentModes[i]]))
		}
	#endif // !NDEBUG
		return details;
	}

	bool IsDeviceSuitable(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices = FindQueueFamilies(device);
		bool extensionsSupported = CheckDeviceExtensionSupport(device);
		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}
		return indices && extensionsSupported && swapChainAdequate;
	}

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			return capabilities.currentExtent;
		}
		else
		{
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);

			VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}

	std::vector<char> ReadFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			throw std::runtime_error(std::string{ "échec de l'ouverture du fichier " } + filename + "!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	VkShaderModule CreateShaderModule(const std::vector<char>& code)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkShaderModule shaderModule;
		if (vkCreateShaderModule(m_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
		{
			throw std::runtime_error("échec de la création d'un module shader!");
		}
		return shaderModule;
	}

	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memProperties);
		for (uint32_t i = 0; i < memProperties.memoryTypeCount; ++i)
		{
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}
		throw std::runtime_error("aucun type de memoire ne satisfait le buffer!");
	}

	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
	{
		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		CREATE_INSTANCE(vkCreateBuffer(m_device, &bufferInfo, nullptr, &buffer), "Vertex buffer creation failed", "Vertex buffer creation success");

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(m_device, buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

		CREATE_INSTANCE(vkAllocateMemory(m_device, &allocInfo, nullptr, &bufferMemory), "Allocation memory failed", "Allocation memory success");

		vkBindBufferMemory(m_device, buffer, bufferMemory, 0);
	}

	// Step : Buffer Intermédiaire
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
	{
		VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0; // Optionnel
		copyRegion.dstOffset = 0; // Optionnel
		copyRegion.size = size;
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

		EndSingleTimeCommands(commandBuffer);
	}

	void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory)
	{
		VkImageCreateInfo imageInfo{};
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width = width;
		imageInfo.extent.height = height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.format = format;
		imageInfo.tiling = tiling;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageInfo.usage = usage;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateImage(m_device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
			throw std::runtime_error("echec de la creation d'une image!");
		}

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(m_device, image, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

		if (vkAllocateMemory(m_device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
		{
			throw std::runtime_error("echec de l'allocation de la memoire d'une image!");
		}

		vkBindImageMemory(m_device, image, imageMemory, 0);
	}

	void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
	{
		VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

		VkImageMemoryBarrier barrier{};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = oldLayout;
		barrier.newLayout = newLayout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = image;
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;

		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else {
			throw std::invalid_argument("transition d'orgisation non supportée!");
		}

		vkCmdPipelineBarrier(
			commandBuffer,
			sourceStage, destinationStage,
			0,
			0, nullptr,
			0, nullptr,
			1, &barrier
		);

		EndSingleTimeCommands(commandBuffer);
	}

	void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
	{
		VkCommandBuffer commandBuffer = BeginSingleTimeCommands();
		VkBufferImageCopy region{};
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;

		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = 1;

		region.imageOffset = { 0, 0, 0 };
		region.imageExtent = {
			width,
			height,
			1
		};

		vkCmdCopyBufferToImage(
			commandBuffer,
			buffer,
			image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&region
		);

		EndSingleTimeCommands(commandBuffer);
	}

	/************************************************************************/
	/* InitFunctions														*/
	/************************************************************************/

	// Create a vulkan instance
	// Step : Instance
	void CreateInstance()
	{
		if (enableValidationLayers && !CheckValidationLayerSupport())
		{
			throw std::runtime_error("les validations layers sont activées mais ne sont pas disponibles!");
		}

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = AppName;
		appInfo.applicationVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
		appInfo.pEngineName = EngineName;
		appInfo.engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		#ifndef NDEBUG
		LOG(TO_TEXT("Nbr of extention for glfw : {}", glfwExtensionCount));
		LOG("Extention list :")
		uint32_t extentionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extentionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, extensions.data());
		for (const auto& extension : extensions)
		{
			LOG(" - " << extension.extensionName)
		}
		#endif // !NDEBUG

		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
			createInfo.ppEnabledLayerNames = m_validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		CREATE_INSTANCE(vkCreateInstance(&createInfo, nullptr, &m_instance), "Création de l'instance failed", "Instance creation success")
	}

	// Select the device that we r going to use to render.
	// Step : Physical devices & Queue Families
	void PickPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
		LOG(TO_TEXT("Number of Device : {}", deviceCount))
		if (deviceCount <= 0)
		{
			throw std::runtime_error("aucune carte graphique ne support vulkan");
		}
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());
		for (const auto& device : devices)
		{
			if (IsDeviceSuitable(device))
			{
				m_physicalDevice = device;
			#ifndef NDEBUG
				VkPhysicalDeviceProperties devicesProperties;
				vkGetPhysicalDeviceProperties(device, &devicesProperties);
				LOG(TO_TEXT("Device selected : {}", devicesProperties.deviceName))
			#endif // !NDEBUG
				break;
			}
		}
		ensure(m_physicalDevice)
	}

	// Step : Logical Device & Queues
	void CreateLogicalDevice()
	{
		QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice);
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		float queuePriority = 1.0f;
		for (const auto& indice : indices)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = indice.value();
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;

			queueCreateInfos.emplace_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		if (indices.Identical())
		{
			createInfo.pQueueCreateInfos = &queueCreateInfos[0];
			createInfo.queueCreateInfoCount = 1;
		}
		else
		{
			createInfo.pQueueCreateInfos = queueCreateInfos.data();
			createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		}

		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = m_deviceExtensions.data();

		createInfo.enabledLayerCount = 0;

		CREATE_INSTANCE(vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device), "Creation Device failed", "Device creation success")

		vkGetDeviceQueue(m_device, indices.Get<GraphicFamily>(), 0, &m_graphicQueue);
		vkGetDeviceQueue(m_device, indices.Get<PresentFamily>(), 0, &m_presentQueue);
	}

	// Step : Window Surface
	void CreateSurface()
	{
		CREATE_INSTANCE(glfwCreateWindowSurface(m_instance, window, nullptr, &m_surface), "Surface creation failed", "Surface creation success")
	}

	// Step : Swap chain
	void CreateSwapchain()
	{
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(m_physicalDevice);

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);
		#ifndef NDEBUG
		LOG("Selection for the swapchain : ");
		LOG(TO_TEXT(" - Surface Format : {}", vulkanFormat[surfaceFormat.format]));
		LOG(TO_TEXT(" - Pres Mode : {}", vulkanPresMode[presentMode]));
		LOG(TO_TEXT(" - Extent2D : w : {}, h : {}", extent.width, extent.height));
		#endif // !NDEBUG

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_surface;

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice);
		uint32_t queueFamilyIndices[] = { indices.Get<GraphicFamily>(), indices.Get<PresentFamily>() };

		if (!indices.Identical())
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0; // Optionnel
			createInfo.pQueueFamilyIndices = nullptr; // Optionnel
		}
		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		CREATE_INSTANCE(vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapChain), "SwapChain creation failed", "Swapchain creation success")

		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, nullptr);
		m_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, m_swapChainImages.data());

		m_swapChainImageFormat = surfaceFormat.format;
		m_swapChainExtent = extent;
	}

	// Step : Image views
	void CreateImageViews()
	{
		m_swapchainImageViews.resize(m_swapChainImages.size());
		for (size_t i = 0; i < m_swapChainImages.size(); ++i)
		{
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_swapChainImages[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = m_swapChainImageFormat;

			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			CREATE_INSTANCE(vkCreateImageView(m_device, &createInfo, nullptr, &m_swapchainImageViews[i]), "failed to create Image view", "Image view creation success")
		}
	}

	// Step : Module Shaders
	void CreateGraphicsPipeline()
	{
		auto vertShaderCode = ReadFile("D:/source/MiniMotor/MiniMotor/Sources/Render/Vulkan/Shaders/vert.spv");
		auto fragShaderCode = ReadFile("D:/source/MiniMotor/MiniMotor/Sources/Render/Vulkan/Shaders/frag.spv");

		auto vertShaderModule = CreateShaderModule(vertShaderCode);
		auto fragShaderModule = CreateShaderModule(fragShaderCode);

		VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		auto bindingDescription = GetVertexBindingDescription();
		auto attributeDescriptions = GetVertexAttributeDescriptions();

		// Step : fonctions fixées
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)m_swapChainExtent.width;
		viewport.height = (float)m_swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		
		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = m_swapChainExtent;

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;
		rasterizer.depthBiasConstantFactor = 0.0f; // Optionnel
		rasterizer.depthBiasClamp = 0.0f; // Optionnel
		rasterizer.depthBiasSlopeFactor = 0.0f; // Optionnel

		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampling.minSampleShading = 1.0f; // Optionnel
		multisampling.pSampleMask = nullptr; // Optionnel
		multisampling.alphaToCoverageEnable = VK_FALSE; // Optionnel
		multisampling.alphaToOneEnable = VK_FALSE; // Optionnel

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optionnel
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optionnel
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optionnel
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optionnel
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optionnel
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optionnel

		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optionnel
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f; // Optionnel
		colorBlending.blendConstants[1] = 0.0f; // Optionnel
		colorBlending.blendConstants[2] = 0.0f; // Optionnel
		colorBlending.blendConstants[3] = 0.0f; // Optionnel

		std::vector<VkDynamicState> dynamicStates = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_LINE_WIDTH
		};

		VkPipelineDynamicStateCreateInfo dynamicState{};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicState.pDynamicStates = dynamicStates.data();

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 1;
		pipelineLayoutInfo.pSetLayouts = &m_descriptorSetLayout;
		pipelineLayoutInfo.pushConstantRangeCount = 0;    // Optionnel
		pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optionnel

		CREATE_INSTANCE(vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout), "pipeline layout failed", "pipeline layout success");

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = nullptr; // Optionnel
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = nullptr; // Optionnel
		pipelineInfo.layout = m_pipelineLayout;
		pipelineInfo.renderPass = m_renderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optionnel
		pipelineInfo.basePipelineIndex = -1; // Optionnel

		CREATE_INSTANCE(vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_graphicsPipeline), "graphic pipelin failed", "graphic pipelin creation success");

		vkDestroyShaderModule(m_device, fragShaderModule, nullptr);
		vkDestroyShaderModule(m_device, vertShaderModule, nullptr);
	}

	// Step : Render pass
	void CreateRenderPass()
	{
		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = m_swapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		// Step : Rendu et présentation
		VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		CREATE_INSTANCE(vkCreateRenderPass(m_device, &renderPassInfo, nullptr, &m_renderPass), "Render passe failed", "Render pass creation success");
	}

	// Step : Frame buffer
	void CreateFrameBuffers()
	{
		m_swapChainFramebuffers.resize(m_swapchainImageViews.size());

		for (size_t i = 0; i < m_swapchainImageViews.size(); ++i) {
			VkImageView attachments[] = {
				m_swapchainImageViews[i]
			};

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_renderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = m_swapChainExtent.width;
			framebufferInfo.height = m_swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("échec de la création d'un framebuffer!");
			}
		}
	}

	// Step Command Buffer
	void CreateCommandPool()
	{
		QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(m_physicalDevice);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFamilyIndices.Get<GraphicFamily>();
		poolInfo.flags = 0; // Optionel

		CREATE_INSTANCE(vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_commandPool), "CommandPool creation failed", "CommandPool creation success")
	}

	void CreateCommandBuffers()
	{
		m_commandBuffers.resize(m_swapChainFramebuffers.size());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

		CREATE_INSTANCE(vkAllocateCommandBuffers(m_device, &allocInfo, m_commandBuffers.data()), "command buffer creation failed", "command buffer creation success");

		for (size_t i = 0; i < m_commandBuffers.size(); ++i)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = 0; // Optionnel
			beginInfo.pInheritanceInfo = nullptr; // Optionel

			if (vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("erreur au début de l'enregistrement d'un command buffer!");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = m_renderPass;
			renderPassInfo.framebuffer = m_swapChainFramebuffers[i];

			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = m_swapChainExtent;

			VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;

			vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);

			VkBuffer vertexBuffer[] = {m_vertexBuffer};
			VkDeviceSize offsets[] = {0};
			vkCmdBindVertexBuffers(m_commandBuffers[i], 0, 1, vertexBuffer, offsets);

			vkCmdBindIndexBuffer(m_commandBuffers[i], m_indexBuffer, 0, VK_INDEX_TYPE_UINT16);

			vkCmdBindDescriptorSets(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1, &m_descriptorSets[i], 0, nullptr);
			vkCmdDrawIndexed(m_commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

			vkCmdDrawIndexed(m_commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

			vkCmdEndRenderPass(m_commandBuffers[i]);

			if (vkEndCommandBuffer(m_commandBuffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("échec de l'enregistrement d'un command buffer!");
			}
		}
	}

	void CreateSyncObjects()
	{
		m_imageAvailableSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
		m_renderFinishedSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
		m_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
		m_imageInFlight.resize(m_swapChainImages.size(), VK_NULL_HANDLE);

		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
		{
			if (vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_imageAvailableSemaphore[i]) != VK_SUCCESS ||
				vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_renderFinishedSemaphore[i]) != VK_SUCCESS ||
				vkCreateFence(m_device, &fenceInfo, nullptr, &m_inFlightFences[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("échec de la création des sémaphores!");
			}
		}
	}

	// Step : Creation de vertex buffers
	void CreateVertexBuffer()
	{
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		CreateBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(m_device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), (size_t)bufferSize);
		vkUnmapMemory(m_device, stagingBufferMemory);

		CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_vertexBuffer, m_vertexBufferMemory);

		CopyBuffer(stagingBuffer, m_vertexBuffer, bufferSize);

		vkDestroyBuffer(m_device, stagingBuffer, nullptr);
		vkFreeMemory(m_device, stagingBufferMemory, nullptr);
	}

	void CreateIndexBuffer()
	{
		VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(m_device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices.data(), (size_t)bufferSize);
		vkUnmapMemory(m_device, stagingBufferMemory);

		CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_indexBuffer, m_indexBufferMemory);

		CopyBuffer(stagingBuffer, m_indexBuffer, bufferSize);

		vkDestroyBuffer(m_device, stagingBuffer, nullptr);
		vkFreeMemory(m_device, stagingBufferMemory, nullptr);
	}

	// Step : Uniform buffer layout
	void CreateDesciptorSetLayout()
	{
		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		uboLayoutBinding.pImmutableSamplers = nullptr; // Optionnel

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 1;
		layoutInfo.pBindings = &uboLayoutBinding;

		CREATE_INSTANCE(vkCreateDescriptorSetLayout(m_device, &layoutInfo, nullptr, &m_descriptorSetLayout), "/!\\ Desciption creation failed /!\\", "Description creation success")
	}

	void CreateUniformBuffers()
	{
		VkDeviceSize bufferSize = sizeof(UniformBufferObject);

		m_uniformBuffers.resize(m_swapChainImages.size());
		m_uniformBuffersMemory.resize(m_swapChainImages.size());

		for (size_t i = 0; i < m_swapChainImages.size(); ++i)
		{
			CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_uniformBuffers[i], m_uniformBuffersMemory[i]);
		}
	}

	void CreateDescriptorPool()
	{
		VkDescriptorPoolSize poolSize{};
		poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSize.descriptorCount = static_cast<uint32_t>(m_swapChainImages.size());

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;

		poolInfo.maxSets = static_cast<uint32_t>(m_swapChainImages.size());

		CREATE_INSTANCE(vkCreateDescriptorPool(m_device, &poolInfo, nullptr, &m_descriptorPool), "Description pool creation failed", "Description pool creation success");
	}

	void CreateDesciptorSets()
	{
		std::vector<VkDescriptorSetLayout> layouts(m_swapChainImages.size(), m_descriptorSetLayout);
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_descriptorPool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(m_swapChainImages.size());
		allocInfo.pSetLayouts = layouts.data();
		m_descriptorSets.resize(m_swapChainImages.size());
		CREATE_INSTANCE(vkAllocateDescriptorSets(m_device, &allocInfo, m_descriptorSets.data()), "Description set failed", "Description set success");

		for (size_t i = 0; i < m_swapChainImages.size(); ++i)
		{
			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = m_uniformBuffers[i];
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(UniformBufferObject);
			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = m_descriptorSets[i];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pBufferInfo = &bufferInfo;
			descriptorWrite.pImageInfo = nullptr; // Optionnel
			descriptorWrite.pTexelBufferView = nullptr; // Optionnel

			vkUpdateDescriptorSets(m_device, 1, &descriptorWrite, 0, nullptr);
		}
	}

	void CreateTextureImage()
	{
		int texWidth, texHeight, texChannels;
		stbi_uc* pixels = stbi_load("Ressources/SunsetIco.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		VkDeviceSize imageSize = texWidth * texHeight * 4;

		if (!pixels) {
			throw std::runtime_error("échec du chargement d'une image!");
		}

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
		void* data;
		vkMapMemory(m_device, stagingBufferMemory, 0, imageSize, 0, &data);
		memcpy(data, pixels, static_cast<size_t>(imageSize));
		vkUnmapMemory(m_device, stagingBufferMemory);

		stbi_image_free(pixels);

		CreateImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_textureImage, m_textureImageMemory);

		TransitionImageLayout(m_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		CopyBufferToImage(stagingBuffer, m_textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
		TransitionImageLayout(m_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

		vkDestroyBuffer(m_device, stagingBuffer, nullptr);
		vkFreeMemory(m_device, stagingBufferMemory, nullptr);
	}

	void initVulkan()
	{
		CreateInstance();

		CreateSurface();
		PickPhysicalDevice();
		CreateLogicalDevice();
		CreateSwapchain();
		CreateImageViews();
		CreateRenderPass();
		CreateDesciptorSetLayout();
		CreateGraphicsPipeline();
		CreateFrameBuffers();
		CreateCommandPool();
		CreateTextureImage();
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateUniformBuffers();
		CreateDescriptorPool();
		CreateDesciptorSets();
		CreateCommandBuffers();
		CreateSyncObjects();
	}

	/************************************************************************/
	/* Functions															*/
	/************************************************************************/

	void CleanUpSwapchain()
	{
		for (auto framebuffer : m_swapChainFramebuffers)
		{
			vkDestroyFramebuffer(m_device, framebuffer, nullptr);
		}

		vkFreeCommandBuffers(m_device, m_commandPool, static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());

		for (size_t i = 0; i < m_swapChainImages.size(); ++i)
		{
			vkDestroyBuffer(m_device, m_uniformBuffers[i], nullptr);
			vkFreeMemory(m_device, m_uniformBuffersMemory[i], nullptr);
		}
		vkDestroyDescriptorPool(m_device, m_descriptorPool, nullptr);
		vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);
		vkDestroyPipeline(m_device, m_graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
		vkDestroyRenderPass(m_device, m_renderPass, nullptr);

		for (auto imageView : m_swapchainImageViews)
		{
			vkDestroyImageView(m_device, imageView, nullptr);
		}
		vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);
	}

	void RecreateSwapchain()
	{
		int width = 0, height = 0;
		glfwGetFramebufferSize(window, &width, &height);
		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(window, &width, &height);
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(m_device);

		CleanUpSwapchain();

		CreateSwapchain();
		CreateImageViews();
		CreateRenderPass();
		CreateGraphicsPipeline();
		CreateFrameBuffers();
		CreateUniformBuffers();
		CreateDescriptorPool();
		CreateCommandBuffers();
	}

	// Function call when the window is resized
	void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		m_framebufferResized = true;
	}

	void UpdateUniformBuffer(uint32_t currentImage)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo{};
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), m_swapChainExtent.width / (float)m_swapChainExtent.height, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		void* data;
		vkMapMemory(m_device, m_uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(m_device, m_uniformBuffersMemory[currentImage]);
	}

}

void VulkanRender::Init()
{
	// initializes the GLFW library
	glfwInit();

	// Cuz it was create for openGl this tell to not create a openGLWin
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// This init the window the four parameter are for which monitor. Last only for openGl
    window = glfwCreateWindow(m_width, m_height, AppName, nullptr, nullptr);
	glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);

	initVulkan();
}

void VulkanRender::Update()
{
	glfwPollEvents();
}

void VulkanRender::Draw()
{
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(m_device, m_swapChain, UINT64_MAX, m_imageAvailableSemaphore[m_currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		RecreateSwapchain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		throw std::runtime_error("swapchain presentation failed!");
	}

	if (m_imageInFlight[imageIndex] != VK_NULL_HANDLE) {
		vkWaitForFences(m_device, 1, &m_imageInFlight[imageIndex], VK_TRUE, UINT64_MAX);
	}
	// Marque l'image comme étant à nouveau utilisée par cette frame
	m_imageInFlight[imageIndex] = m_inFlightFences[m_currentFrame];

	UpdateUniformBuffer(imageIndex);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphore[m_currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_commandBuffers[imageIndex];

	VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphore[m_currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(m_device, 1, &m_inFlightFences[m_currentFrame]);

	if (vkQueueSubmit(m_graphicQueue, 1, &submitInfo, m_inFlightFences[m_currentFrame]) != VK_SUCCESS)
	{
		throw std::runtime_error("échec de l'envoi d'un command buffer!");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { m_swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;

	presentInfo.pResults = nullptr; // Optionnel

	result = vkQueuePresentKHR(m_presentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_framebufferResized)
	{
		m_framebufferResized = false;
		RecreateSwapchain();
	}
	else if (result != VK_SUCCESS)
	{
		throw std::runtime_error("échec de la présentation d'une image!");
	}

	m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

bool VulkanRender::IsWindowOpen() const
{
	return !glfwWindowShouldClose(window);
}

void VulkanRender::BufferFrame(const VertexArray2D& vertexArray)
{
}

void VulkanRender::HandleEvents()
{
}

void VulkanRender::ClearWindow()
{
}

void VulkanRender::CloseWindow()
{
	vkDeviceWaitIdle(m_device);
	CleanUpSwapchain();
	vkDestroyImage(m_device, m_textureImage, nullptr);
	vkFreeMemory(m_device, m_textureImageMemory, nullptr);
	vkDestroyBuffer(m_device, m_indexBuffer, nullptr);
	vkFreeMemory(m_device, m_indexBufferMemory, nullptr);
	vkDestroyBuffer(m_device, m_vertexBuffer, nullptr);
	vkFreeMemory(m_device, m_vertexBufferMemory, nullptr);
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
	{
		vkDestroySemaphore(m_device, m_renderFinishedSemaphore[i], nullptr);
		vkDestroySemaphore(m_device, m_imageAvailableSemaphore[i], nullptr);
		vkDestroyFence(m_device, m_inFlightFences[i], nullptr);
	}
	vkDestroyCommandPool(m_device, m_commandPool, nullptr);
	vkDestroyDevice(m_device, nullptr);
	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	vkDestroyInstance(m_instance, nullptr);

	glfwDestroyWindow(window);
	glfwTerminate();
}

void VulkanRender::DrawSlate(SContainer* slate)
{
}

void VulkanRender::DrawLine(const FVec2& start, const FVec2& end, const FColor& color)
{
}

void VulkanRender::DrawQuad(const FVec2& position, const FVec2& size, const FColor& color)
{
}
