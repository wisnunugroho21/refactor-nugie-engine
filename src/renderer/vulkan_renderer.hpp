#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>

#include "../window/glfw_window.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete();
};

struct Vertex {
	glm::vec2 pos;
	glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};

const std::vector<Vertex> vertices = {
	{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
	{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

class VulkanRenderer {
public:
	bool framebufferResized = false;

	void draw(GlfwAppWindow &window);
	void waitIdle();

	VulkanRenderer(GlfwAppWindow &window);
	~VulkanRenderer();

private:
	uint32_t currentFrame = 0;

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;

	// device
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	// Queue
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	// Swapchain
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	// pipeline
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	// buffer
	VkCommandPool commandPool;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	std::vector<VkCommandBuffer> commandBuffers;

	// sync
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	// load model
	void createVertexBuffer();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void drawFrame(GlfwAppWindow &window);

	// init
	void initVulkan(GlfwAppWindow &window);

	void createInstance();
	void setupDebugMessenger();
	void createSurface(GlfwAppWindow &window);
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain(GlfwAppWindow &window);
	void createImageViews();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createSyncObjects();
	
	VkShaderModule createShaderModule(const std::vector<char>& code);

	// destroy
	void cleanupSwapChain();
	void cleanup();

	// for every time window resizing
	void recreateSwapChain(GlfwAppWindow &window);

	// check memory before send buffer
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	// check & setup vulkan
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GlfwAppWindow &window);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	std::vector<const char*> getRequiredExtensions();
	bool checkValidationLayerSupport();

	static std::vector<char> readFile(const std::string& filename);
};