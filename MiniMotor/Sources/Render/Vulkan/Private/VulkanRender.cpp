// Copyright Shimmer Studios : All rights reserved.

#include "VulkanRender.h"

// @WinSpec - Begin
#define VK_USE_PLATFORM_WIN32_KHR
// @WinSpec - End
// This allow glfw to include it's requirement for vulkan
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
// @WinSpec - Begin
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
// @WinSpec - End

namespace
{
	MAKE_STATE(GraphicFamily)
	MAKE_STATE(PresentFamily)

	using QueueFamily = Typelist<GraphicFamily, PresentFamily>;

	/************************************************************************/
	/* Parameters															*/
	/************************************************************************/

	GLFWwindow* window = nullptr;
	const uint32_t m_width = 800;
	const uint32_t m_height = 600;

	// A instance is a connection between the app and VulkLib
	VkInstance instance;

	VkSurfaceKHR surface;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	VkDevice device;

	VkQueue graphicsQueue;

	VkQueue presentQueue;

	const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	VkSwapchainKHR swapChain;

	std::vector<VkImage> swapChainImages;

	VkFormat swapChainImageFormat;

	VkExtent2D swapChainExtent;

	std::vector<VkImageView> swapChainImageViews;

	/************************************************************************/
	/* Functions															*/
	/************************************************************************/

	template <typename QueueType>
	class QueueFamillyIndices_T
	{
	public:
		template <typename IndiceType>
		const QueueType& Get() const
		{
			static_assert(IsTypeInList<IndiceType, QueueFamily>::value, "Indice type isn't in the list");
			return Indices[GetTypelistIndex<IndiceType, QueueFamily>::value].value();
		}

		template <typename IndiceType>
		void SetIndice(const QueueType& val)
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

	private:
		std::array<std::optional<QueueType>, GetSizelist<QueueFamily>::value>  Indices;
	};

	using QueueFamillyIndices = QueueFamillyIndices_T<uint32_t>;

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities{};
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	// Populate the swapchain struct
	SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& device)
	{
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
		
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount > 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}
		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
		if (presentModeCount > 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
		}
		return details;
	}

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return availableFormat;
			}
		}
		return availableFormats[0];
	}

	VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresenMode : availablePresentModes)
		{
			if (availablePresenMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return availablePresenMode;
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
			VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
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
			throw std::runtime_error("failed to open file!");
		}

		size_t filesize = (size_t)file.tellg();
		std::vector<char> buffer(filesize);

		file.seekg(0);
		file.read(buffer.data(), filesize);
		file.close();

		return buffer;
	}

	// Create the instance of the vulkan
	void CreateInstance()
	{
		// Init with {} init list for the struct to be nullptr
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Vulkan Test";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "MiniMotor";
		appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// @Detail - Begin : cuz vulkan is not win dependante it need to know the target win which was create by glfw for window in our case
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtentions;

		glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtentions;
		// @Detail - End : cuz vulkan is not win dependante it need to know the target win which was create by glfw for window in our case

		createInfo.enabledLayerCount = 0;

		//	Pointer to struct with creation info
		//	Pointer to custom allocator callbacks, always nullptr in this tutorial
		//	Pointer to the variable that stores the handle to the new object
		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create instance!");
		}
	}

	void CreateSurface()
	{
		VkWin32SurfaceCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd = glfwGetWin32Window(window);
		createInfo.hinstance = GetModuleHandle(nullptr);

		if (vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface) != VK_SUCCESS)
		{
			throw std::runtime_error("Bro the surface win is not here");
		}
	}

	QueueFamillyIndices FindQueueFamillies(const VkPhysicalDevice& device)
	{
		QueueFamillyIndices indices;

		uint32_t queueFamilyCount = 0;

		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);


		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		for (int i = 0; i < queueFamilyCount; ++i)
		{
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
			if (presentSupport)
			{
				indices.SetIndice<PresentFamily>(i);
			}

			if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.SetIndice<GraphicFamily>(i);
			}

			// Break the search
			if (indices)
				break;
		}

		return indices;
	}

	bool CheckDeviceExtentionSupported(const VkPhysicalDevice& device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::vector<std::string> RequiredExtensions;

		for (auto extension : deviceExtensions)
		{
			RequiredExtensions.emplace_back(extension);
		}

		for (const auto& extension : availableExtensions)
		{
			std::cout << extension.extensionName << std::endl;
			std::erase_if(RequiredExtensions, [&](const std::string& str) { return str == extension.extensionName; });
		}

		return RequiredExtensions.empty();
	}

	bool isDeviceSuitable(const VkPhysicalDevice& device)
	{
		QueueFamillyIndices indices = FindQueueFamillies(device);
		bool extentionSupported = CheckDeviceExtentionSupported(device);

		bool swapChainAdequate = false;
		if (extentionSupported)
		{
			SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices && extentionSupported && swapChainAdequate;
	}

	// Cuz Vulk need to select manually a target device.
	void PickPhysicalDevice()
	{
		uint32_t deviceCount = 0;

		// First call to retrive the data size and check if there any.
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
		if (deviceCount <= 0)
		{
			throw std::runtime_error("Bro go by a CG cause no display");
		}

		// Second call to create the vector data with the correct size so no need to resize at runtime.
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		for (const auto& device : devices)
		{
			if (isDeviceSuitable(device))
			{
				physicalDevice = device;
				break;
			}
		}

		if (physicalDevice == VK_NULL_HANDLE)
		{
			throw std::runtime_error("No suitable device found");
		}
	}

	void CreateLogicalDevice()
	{
		QueueFamillyIndices indices = FindQueueFamillies(physicalDevice);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		
		// Can assign priority btw 0.0 & 1.0
		float queuePriority = 1.f;
		for (auto& queueFamily : indices)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily.value();
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		// Todo : we will come back later...
		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		createInfo.enabledLayerCount = 0;

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create logical device");
		}

		// Retrive the queue
		vkGetDeviceQueue(device, indices.Get<PresentFamily>(), 0, &presentQueue);
		vkGetDeviceQueue(device, indices.Get<GraphicFamily>(), 0, &graphicsQueue);
	}

	void CreateSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(physicalDevice);

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = ChoosePresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamillyIndices indices = FindQueueFamillies(physicalDevice);
		uint32_t queueFamilyIndices[] = {indices.Get<GraphicFamily>(), indices.Get<PresentFamily>()};

		if (indices.Get<GraphicFamily>() != indices.Get<PresentFamily>())
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
		swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

		swapChainImageFormat = surfaceFormat.format;
		swapChainExtent = extent;
	}

	void CreateImageViews()
	{
		swapChainImageViews.resize(swapChainImages.size());
		for (size_t i = 0; i < swapChainImageViews.size(); ++i)
		{
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = swapChainImages[i];

			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = swapChainImageFormat;

			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create the image view");
			}
		}
	}

	VkShaderModule CreateShaderModule(const std::vector<char>& code)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
		VkShaderModule shaderModule;
		if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create shader module");
		}
		return shaderModule;
	}

	void CreateGraphicsPipeline()
	{
		auto fragShaderCode = ReadFile("D:/source/MiniMotor/MiniMotor/Sources/Render/Vulkan/Shaders/frag.spv");
		auto vertShaderCode = ReadFile("D:/source/MiniMotor/MiniMotor/Sources/Render/Vulkan/Shaders/vert.spv");
		std::cout << "frag size : " << fragShaderCode.size() << ", vert size : " << vertShaderCode.size() << std::endl;

		VkShaderModule fragShaderModule = CreateShaderModule(fragShaderCode);
		VkShaderModule vertShaderModule = CreateShaderModule(vertShaderCode);

		// tell which part of the shader it is
		VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;

		// ok indicate which module it is and the entry point. can combine multiple shader in one file with multi entrypoint
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderModule.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		std::vector<SDynamicState> dynamicStates = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};

		VkPipelineDynamicStateCreateInfo dynamicState{};

		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicState.pDynamicStates = dynamicStates.data();

		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 0;
		vertexInputInfo.pVertexBindingDescription = nullptr;
		vertexInputInfo.vertexAttributeDescriptionCount = 0;
		vertexInputInfo.pVertexAttributionDescriptions = nullptr;

		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)swapChainExtent.width;
		viewport.height = (float)swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		VkRect2D scissor{};
		scissor.offset = {0; 0};

		vkDestroyShaderModule(device, fragShaderModule, nullptr);
		vkDestroyShaderModule(device, vertShaderModule, nullptr);
	}

	void initVulkan()
	{
		CreateInstance();
		// Here u can setup debug message and layer validation
		CreateSurface();
		PickPhysicalDevice();
		CreateLogicalDevice();
		CreateSwapChain();
		CreateImageViews();
		CreateGraphicsPipeline();
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
    window = glfwCreateWindow(m_width, m_height, "Vulkan window", nullptr, nullptr);

	initVulkan();
}

void VulkanRender::Update()
{
	glfwPollEvents();
}

void VulkanRender::Draw()
{
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
	for (auto& imageView : swapChainImageViews)
	{
		vkDestroyImageView(device, imageView, nullptr);
	}
	vkDestroySwapchainKHR(device, swapChain, nullptr);
	vkDestroyDevice(device, nullptr);
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);

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
