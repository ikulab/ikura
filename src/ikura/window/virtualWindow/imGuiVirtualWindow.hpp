#pragma once

#include <imgui/imgui.h>

#include "../nativeWindow/glfwNativeWindow.hpp"
#include "./virtualWindow.hpp"

namespace ikura {
struct ImGuiVirtualWindowInitConfig {
    const char *fontFilePath;
    float fontSizePixels;
};

class ImGuiVirtualWindow : public VirtualWindow {
  protected:
    std::shared_ptr<GlfwNativeWindow> nativeWindow;
    ImGuiContext *imGuiContext;

    vk::DescriptorPool imGuiDescriptorPool;

    void initImGuiResources(ImGuiVirtualWindowInitConfig *initConfig);
    void destroyImGuiResources();

  public:
    ImGuiVirtualWindow(std::shared_ptr<RenderEngine> renderEngine,
                       std::shared_ptr<GlfwNativeWindow> nativeWindow,
                       ImGuiVirtualWindowInitConfig *initConfig);
    ~ImGuiVirtualWindow();

    void recordCommandBuffer(vk::CommandBuffer cmdBuffer) override;
    bool isFocused() const override;

    void setCurrentImGuiContext() const;
    void newFrame();
};
} // namespace ikura