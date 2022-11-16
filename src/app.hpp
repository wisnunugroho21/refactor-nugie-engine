#include "window/glfw_window.hpp"
#include "renderer/vulkan_renderer.hpp"

class App
{
private:
    GlfwAppWindow *window;
    VulkanRenderer *render;

public:
    App();
    ~App();
    
    void run();
};
