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

	template <typename QueueType>
	class QueueFamillyIndices_T
	{
	public:
		template <typename IndiceType>
		const QueueType& GetIndice() const
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

	bool isDeviceSuitable(const VkPhysicalDevice& device)
	{
		QueueFamillyIndices indices = FindQueueFamillies(device);

		return indices;
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

		createInfo.enabledExtensionCount = 0;

		createInfo.enabledLayerCount = 0;

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create logical device");
		}

		// Retrive the queue
		vkGetDeviceQueue(device, indices.GetIndice<PresentFamily>(), 0, &presentQueue);
		vkGetDeviceQueue(device, indices.GetIndice<GraphicFamily>(), 0, &graphicsQueue);
	}

	void initVulkan()
	{
		CreateInstance();
		// Here u can setup debug message and layer validation
		CreateSurface();
		PickPhysicalDevice();
		CreateLogicalDevice();
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