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
    const int MAX_FRAMES_IN_FLIGHT = 2;
    ANativeWindow* window;
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkPhysicalDevice GPU = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkSwapchainKHR swap_chain = VK_NULL_HANDLE;
    VkDescriptorSetLayout descriptor_layout = VK_NULL_HANDLE;
    VkPipelineLayout pipeline_layout = VK_NULL_HANDLE;
    VkPipeline graphics_pipeline = VK_NULL_HANDLE;
    VkExtent2D swap_chain_extent;
    VkFormat swap_chain_format;
    VkRenderPass render_pass;
    VkCommandPool command_pool;
    VkDescriptorPool descriptor_pool;
    std::vector<VkDescriptorSet> descriptor_sets;
    std::vector<VkImageView> image_views;
    std::vector<VkFramebuffer> framebuffers;
    std::vector<VkCommandBuffer> command_buffers;
    std::vector<VkSemaphore> image_available_semaphores;
    std::vector<VkSemaphore> render_finished_semaphores;
    std::vector<VkFence> in_flight_fences;
    uint32_t cur_frame = 0;
    VkBuffer VBO, EBO;
    VkDeviceMemory VBO_mem, EBO_mem;
    VkImage texture_image;
    VkDeviceMemory texture_image_mem;
    std::vector<VkBuffer> UBOs;
    std::vector<VkDeviceMemory> UBO_mems;
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
    void create_layout_descriptor();
    void create_descriptor_pool();
    void create_descriptor_sets();
    void create_graphics_pipeline();
    void alloc_framebuffers();
    void create_command_pool();
    void alloc_command_buffers();
    void create_texture_image();
    VkShaderModule create_shader_mode(const u_int8_t* bytes, size_t size_in_bytes);
    void attach_surface();
    void create_render_pass();
    void create_sync_objects();
    void create_buffers();
    void create_image(uint32_t, uint32_t, VkFormat, VkImageTiling, VkImageUsageFlags, VkMemoryPropertyFlags, VkImage&, VkDeviceMemory&);
    void create_buffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, VkBuffer&, VkDeviceMemory&);
    void copy_buffer(VkBuffer /*src*/, VkBuffer /*dst*/, VkDeviceSize /*size*/);
    void record_command_buffer(VkCommandBuffer /*buffer*/, u_int32_t /*image index*/);
    uint32_t find_mem_type(uint32_t filter, VkMemoryPropertyFlags properties);
    void update_uniform_buffer();
public:
    explicit VkContext(ANativeWindow* _window);
    virtual ~VkContext();
    void present();
};


#endif //HELLO_VULKAN_VKCONTEXT_H
