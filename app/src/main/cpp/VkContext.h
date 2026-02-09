//
// Created by 86187 on 2026/2/6.
//

#ifndef HELLO_VULKAN_VKCONTEXT_H
#define HELLO_VULKAN_VKCONTEXT_H
#include <vector>
#include <android/native_window.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>

struct SwapChainDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> modes;
};

struct SwapChainFormat {
    VkSurfaceFormatKHR image_format;
    VkPresentModeKHR mode;
    VkExtent2D extent;
    u_int32_t min_image_count;
};

class VkContext {
private:
    ANativeWindow* window;
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkSwapchainKHR swap_chain = VK_NULL_HANDLE;
    VkPipelineLayout pipeline_layout = VK_NULL_HANDLE;
    VkPipeline graphics_pipeline = VK_NULL_HANDLE;
    VkExtent2D swap_chain_extent;
    VkFormat swap_chain_format;
    VkRenderPass render_pass;
    std::vector<VkImageView> image_views;
    SwapChainDetails swap_chain_details{};
    u_int32_t graphics_queue_index = 0;
    VkPhysicalDevice find_gpu();
    bool is_suitable(VkPhysicalDevice gpu);
    bool find_queue_families(VkPhysicalDevice gpu);
    void query_swap_chain_details(VkPhysicalDevice gpu);
    SwapChainFormat choose_swap_chain_format();
    void create_instance();
    void create_logic_device();
    void create_swap_chain();
    void create_graphics_pipeline();
    VkShaderModule create_shader_mode(const u_int8_t* bytes, size_t size_in_bytes);
    void attach_surface();
    void create_render_pass();
public:
    explicit VkContext(ANativeWindow* _window);
    virtual ~VkContext();
};


#endif //HELLO_VULKAN_VKCONTEXT_H
