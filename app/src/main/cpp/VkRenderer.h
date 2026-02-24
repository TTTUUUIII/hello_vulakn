//
// Created by wn123 on 2026-02-14.
//

#ifndef HELLO_VULKAN_VKRENDERER_H
#define HELLO_VULKAN_VKRENDERER_H
#include <jni.h>
#include <thread>
#include "VkContext.h"

enum class renderer_state_t {
    INVALID,
    PREPARED,
    RUNNING,
    PAUSED
};

class VkRenderer {
private:
    std::unique_ptr<VkContext> context;
    ANativeWindow* window;
    std::thread vk_thread;
    std::atomic<bool> vk_thread_running = false;
    std::atomic<renderer_state_t> state = renderer_state_t::INVALID;
    void on_draw();
public:
    explicit VkRenderer(JNIEnv *env, jobject activity, jobject surface);
    ~VkRenderer();
    bool request_start();
    void request_pause();
    void request_resume();
    void release();
};


#endif //HELLO_VULKAN_VKRENDERER_H
