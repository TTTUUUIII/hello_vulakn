//
// Created by 86187 on 2026/2/6.
//

#ifndef HELLO_VULKAN_VKCONTEXT_H
#define HELLO_VULKAN_VKCONTEXT_H
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>
#include <android/native_window_jni.h>

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
    VkCommandPool command_pool;
    std::vector<VkImageView> image_views;
    std::vector<VkFramebuffer> framebuffers;
    VkCommandBuffer command_buffer;
    VkSemaphore image_available_semaphore;
    VkSemaphore render_finished_semaphore;
    VkFence in_flight_fence;
    SwapChainDetails swap_chain_details{};
    u_int32_t queue_index = 0;
    VkQueue queue;
    VkPhysicalDevice find_gpu();
    bool is_suitable(VkPhysicalDevice gpu);
    bool find_queue_families(VkPhysicalDevice gpu);
    void query_swap_chain_details(VkPhysicalDevice gpu);
    SwapChainFormat choose_swap_chain_format();
    void create_instance();
    void create_logic_device();
    void create_swap_chain();
    void create_graphics_pipeline();
    void alloc_framebuffers();
    void create_command_pool();
    void alloc_command_buffers();
    VkShaderModule create_shader_mode(const u_int8_t* bytes, size_t size_in_bytes);
    void attach_surface();
    void create_render_pass();
    void create_sync_objects();
public:
    explicit VkContext(ANativeWindow* _window);
    virtual ~VkContext();
    void submit_command(uint32_t index);
    uint32_t acquire_next_image();
    void wait_idle();
};


#endif //HELLO_VULKAN_VKCONTEXT_H
