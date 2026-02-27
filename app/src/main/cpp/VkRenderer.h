//
// Created by wn123 on 2026-02-14.
//

#ifndef HELLO_VULKAN_VKRENDERER_H
#define HELLO_VULKAN_VKRENDERER_H
#include <jni.h>
#include <thread>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VkContext.h"

enum renderer_state_t {
    INVALID,
    PREPARED,
    RUNNING,
    PAUSED
};

class VkRenderer {
private:
    const int MAX_FRAMES_IN_FLIGHT = 2;
    std::unique_ptr<VkContext> context;
    ANativeWindow* window;
    std::thread vk_thread;
    std::atomic<bool> vk_thread_running = false;
    std::atomic<renderer_state_t> state = renderer_state_t::INVALID;
    VkDevice device;
    VkPhysicalDevice phy_device;
    swap_chain_format_t format;
    VkRenderPass render_pass;
    VkDescriptorSetLayout descriptor_layout;
    VkDescriptorPool descriptor_pool;
    std::vector<VkDescriptorSet> descriptor_sets;
    VkPipelineLayout pipeline_layout;
    VkPipeline pipeline;
    VkCommandPool command_pool;
    VkImage tex;
    VkImageView tex_view;
    VkDeviceMemory tex_mem;
    VkSampler tex_sampler;
    VkSwapchainKHR swap_chain;
    queue_info_t graphics_queue_info;
    queue_info_t present_queue_info;
    VkBuffer VBO, EBO;
    VkDeviceMemory VBO_mem, EBO_mem;
    std::vector<VkBuffer> UBOs;
    std::vector<VkDeviceMemory> UBO_mems;
    std::vector<VkImageView> image_views;
    std::vector<VkFramebuffer> framebuffers;
    std::vector<VkCommandBuffer> command_buffers;
    std::vector<VkSemaphore> image_available_semaphores;
    std::vector<VkSemaphore> render_finished_semaphores;
    std::vector<VkFence> in_flight_fences;
    uint32_t cur_frame = 0;
    void create_swap_chain_views();
    void create_render_pass();
    void create_layout_descriptor();
    void create_descriptor_pool();
    void create_descriptor_sets();
    void create_graphics_pipeline();
    void create_framebuffers();
    void create_command_pool();
    void create_command_buffers();
    void create_texture();
    void create_texture_sampler();
    void create_buffers();
    void create_sync_objects();
    void create_buffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, VkBuffer&, VkDeviceMemory&);
    void copy_buffer(VkBuffer /*src*/, VkBuffer /*dst*/, VkDeviceSize /*size*/);
    void copy_image_buffer(VkBuffer /*buffer*/, VkImage /*image*/, uint32_t /*width*/, uint32_t /*height*/);
    uint32_t find_mem_type(uint32_t filter, VkMemoryPropertyFlags properties);
    VkShaderModule create_shader_mode(const u_int8_t* bytes, size_t size_in_bytes);
    void create_image(uint32_t, uint32_t, VkFormat, VkImageTiling, VkImageUsageFlags, VkMemoryPropertyFlags, VkImage&, VkDeviceMemory&);
    void transition_layout(VkImage, VkFormat, VkImageLayout /*old_layout*/, VkImageLayout /*new_layout*/);
    void begin_single_time_commands(VkCommandBuffer&);
    void end_single_time_commands(VkCommandBuffer);
    void update_uniform_buffer();
    void record_command_buffer(VkCommandBuffer /*buffer*/, u_int32_t /*image index*/);
    void on_begin();
    void on_draw();
    void on_end();
public:
    explicit VkRenderer(JNIEnv *env, jobject activity, jobject surface);
    ~VkRenderer();
    bool request_start();
    void request_pause();
    void request_resume();
    void release();
};


#endif //HELLO_VULKAN_VKRENDERER_H
