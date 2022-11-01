#pragma once

#include <chrono>
#include <memory>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../window/nativeWindow/glfwNativeWindow.hpp"
#include "../window/virtualWindow/imGuiVirtualWindow.hpp"
#include "./renderEngine/renderEngine.hpp"

namespace ikura {
class AppEngine {
    std::shared_ptr<RenderEngine> renderEngine;
    std::vector<std::shared_ptr<NativeWindow>> nativeWindows;

    float fps = 60.0;
#ifdef __APPLE__
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point currentTime;
#else
    std::chrono::_V2::system_clock::time_point startTime;
    std::chrono::_V2::system_clock::time_point currentTime;
#endif
    float secondsFromStart;
    float deltaTime;

  public:
    AppEngine(std::shared_ptr<RenderEngine> renderEngine);

    void addWindow(std::shared_ptr<GlfwNativeWindow> glfwNativeWindow);

    void vSync();
    void setStartTime();
    float getSecondsFromStart() const;
    float getDeltaTime() const;

    int shouldTerminated();
    void drawAllWindows();
    void destroyClosedWindow();
};
} // namespace ikura