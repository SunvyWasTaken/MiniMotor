// Copyright Shimmer Studios : All rights reserved.

#include "VulkanRender.h"

// This allow glfw to include it's requirement for vulkan
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

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

	/************************************************************************/
	/* Parameters															*/
	/************************************************************************/

	const char* AppName = "Vulkan Test";
	const char* EngineName = "MiniMotor";

	GLFWwindow* window = nullptr;
	const uint32_t m_width = 800;
	const uint32_t m_height = 600;

	// A instance is a connection between the app and VulkLib
	VkInstance m_instance;

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

	VkPipeline m_graphicsPipeline;

	std::vector<VkFramebuffer> m_swapChainFramebuffers;

	VkCommandPool m_commandPool;

	std::vector<VkCommandBuffer> m_commandBuffers;

	VkSemaphore m_imageAvailableSemaphore;

	VkSemaphore m_renderFinishedSemaphore;

	/************************************************************************/
	/* FuncUtils															*/
	/************************************************************************/

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
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return capabilities.currentExtent;
		}
		else {
			VkExtent2D actualExtent = { m_width, m_height };

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

	/************************************************************************/
	/* Functions															*/
	/************************************************************************/

	// Create a vulkan instance
	// Step : Instance
	void CreateInstance()
	{
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

		createInfo.enabledLayerCount = 0;

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
		for (size_t i = 0; i < m_swapChainImages.size(); i++)
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
		auto vertShaderCode = ReadFile("Shaders/vert.spv");
		auto fragShaderCode = ReadFile("Shaders/frag.spv");

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

		// Step : fonctions fixées
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 0;
		vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optionnel
		vertexInputInfo.vertexAttributeDescriptionCount = 0;
		vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optionnel

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
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
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
		pipelineLayoutInfo.setLayoutCount = 0;            // Optionnel
		pipelineLayoutInfo.pSetLayouts = nullptr;         // Optionnel
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

	void CreateFrameBuffer()
	{
		m_swapChainFramebuffers.resize(m_swapchainImageViews.size());

		for (size_t i = 0; i < m_swapchainImageViews.size(); i++) {
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

	void CreateCommandPool()
	{
		QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(m_physicalDevice);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFamilyIndices.Get<GraphicFamily>();
		poolInfo.flags = 0; // Optionel

		CREATE_INSTANCE(vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_commandPool), "CommandPool creation failed", "CommandPool creation success")
	}

	void CreatCommandBuffers()
	{
		m_commandBuffers.resize(m_swapChainFramebuffers.size());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

		CREATE_INSTANCE(vkAllocateCommandBuffers(m_device, &allocInfo, m_commandBuffers.data()), "command buffer creation failed", "command buffer creation success");

		for (size_t i = 0; i < m_commandBuffers.size(); i++)
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

			vkCmdDraw(m_commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(m_commandBuffers[i]);

			if (vkEndCommandBuffer(m_commandBuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("échec de l'enregistrement d'un command buffer!");
			}
		}
	}

	void CreateSemaphores()
	{
		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		if (vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_imageAvailableSemaphore) != VK_SUCCESS ||
			vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_renderFinishedSemaphore) != VK_SUCCESS) {

			throw std::runtime_error("échec de la création des sémaphores!");
		}
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
		CreateGraphicsPipeline();
		CreateFrameBuffer();
		CreateCommandPool();
		CreatCommandBuffers();
		CreateSemaphores();
	}
}

void VulkanRender::Init()
{
	// initializes the GLFW library
	glfwInit();

	// Cuz it was create for openGl this tell to not create a openGLWin
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// Cuz Resize take a bit more work disable for now
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// This init the window the four parameter are for which monitor. Last only for openGl
    window = glfwCreateWindow(m_width, m_height, AppName, nullptr, nullptr);

	initVulkan();
}

void VulkanRender::Update()
{
	glfwPollEvents();
}

void VulkanRender::Draw()
{
	uint32_t imageIndex;
	vkAcquireNextImageKHR(m_device, m_swapChain, UINT64_MAX, m_imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphore };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_commandBuffers[imageIndex];

	VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(m_graphicQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
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

	vkQueuePresentKHR(m_presentQueue, &presentInfo);
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
	vkDestroySemaphore(m_device, m_renderFinishedSemaphore, nullptr);
	vkDestroySemaphore(m_device, m_imageAvailableSemaphore, nullptr);

	vkDestroyCommandPool(m_device, m_commandPool, nullptr);

	for (auto framebuffer : m_swapChainFramebuffers) {
		vkDestroyFramebuffer(m_device, framebuffer, nullptr);
	}
	vkDestroyPipeline(m_device, m_graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
	vkDestroyRenderPass(m_device, m_renderPass, nullptr);

	for (auto imageView : m_swapchainImageViews)
	{
		vkDestroyImageView(m_device, imageView, nullptr);
	}
	vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);

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
