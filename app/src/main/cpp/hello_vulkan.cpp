#include <jni.h>
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>
#include <android/native_window_jni.h>
#include "VkContext.h"
#include "Log.h"
const char* TAG = "hello_vulkan";
//std::unique_ptr<VkContext> context;

extern "C"
JNIEXPORT void JNICALL
Java_cn_touchair_hello_1vulkan_MainActivity_nativeAttachSurface(JNIEnv *env, jobject thiz,jobject surface) {
    std::unique_ptr<VkContext> context = std::make_unique<VkContext>(ANativeWindow_fromSurface(env, surface));
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_touchair_hello_1vulkan_MainActivity_nativeDetachSurface(JNIEnv *env, jobject thiz) {
//    context = nullptr;
}