//
// Created by wn123 on 2026-02-14.
//

#include "VkRenderer.h"
#include "Log.h"

static const char* TAG = "VkRenderer";

VkRenderer::VkRenderer(JNIEnv *env, jobject activity, jobject surface) {
    window = ANativeWindow_fromSurface(env, surface);
    context = std::make_unique<VkContext>(window);
    state = renderer_state_t::PREPARED;
}

VkRenderer::~VkRenderer() = default;

bool VkRenderer::request_start() {
    LOGD(TAG, "request_start %d", state.load());
    if (state != renderer_state_t::PREPARED) return false;
    vk_thread = std::thread([this]() {
        vk_thread_running = true;
        LOGI(TAG, "VkThread started, tid=%d", gettid());
        for (;;) {
            if (state == renderer_state_t::RUNNING) {
                on_draw();
            } else if (state == renderer_state_t::PAUSED) {
                state.wait(renderer_state_t::PAUSED);
            } else {
                break;
            }
        }
        context->wait_idle();
        vk_thread_running.store(false);
        vk_thread_running.notify_one();
        LOGI(TAG, "VkThread exited, tid=%d", gettid());
    });
    state = renderer_state_t::RUNNING;
    vk_thread.detach();
    return true;
}

void VkRenderer::request_pause() {
    if (state == renderer_state_t::RUNNING) {
        state = renderer_state_t::PAUSED;
    }
}

void VkRenderer::request_resume() {
    if (state == renderer_state_t::PAUSED) {
        state = renderer_state_t::RUNNING;
        state.notify_one();
    }
}

void VkRenderer::release() {
    if (state == renderer_state_t::INVALID) return;
    state = renderer_state_t::INVALID;
    state.notify_one();
    vk_thread_running.wait(true);
    ANativeWindow_release(window);
}

void VkRenderer::on_draw() {
    uint32_t index = context->acquire_next_image();
    context->submit_command(index);
}
