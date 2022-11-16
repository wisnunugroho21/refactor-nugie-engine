#include "app.hpp"

static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto app = reinterpret_cast<VulkanRenderer*>(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
}

App::App() {
	this->window = new GlfwAppWindow(800, 600, "Vulkan Tutorial", framebufferResizeCallback);
	this->render = new VulkanRenderer(*this->window);
}

void App::run() {
	while(!this->window->shouldClose()) {
		this->window->pollEvents();
		this->render->draw(*this->window);
	}

	this->render->waitIdle();
}
