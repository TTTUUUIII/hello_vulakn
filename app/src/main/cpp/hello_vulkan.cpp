#include <jni.h>
#include <vector>
#include "VkRenderer.h"
#include "Log.h"
const char* TAG = "hello_vulkan";
std::unique_ptr<VkRenderer> renderer;

extern "C"
JNIEXPORT void JNICALL
Java_cn_touchair_hello_1vulkan_MainActivity_nativeAttachSurface(JNIEnv *env, jobject thiz,jobject surface) {
   renderer = std::make_unique<VkRenderer>(env, nullptr, surface);
   renderer->request_start();
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_touchair_hello_1vulkan_MainActivity_nativeDetachSurface(JNIEnv *env, jobject thiz) {
    renderer->release();
    renderer = nullptr;
}