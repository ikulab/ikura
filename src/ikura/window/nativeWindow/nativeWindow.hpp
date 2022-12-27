#pragma once

#include <memory>
#include <vector>

#include <vulkan/vulkan.hpp>

#include "../../engine/renderEngine/renderEngine.hpp"
#include "../window.hpp"

namespace ikura {
class VirtualWindow;

class NativeWindow : public Window {
  protected:
    vk::SurfaceKHR surface;
    vk::SwapchainKHR swapChain;
    vk::Format swapChainFormat;
    vk::Extent2D swapChainExtent;

    std::vector<vk::Image> swapChainImages;
    uint32_t currentFrame = 0;
    bool swapChainResized = false;

    std::shared_ptr<RenderTarget> renderTarget;

    std::vector<std::shared_ptr<VirtualWindow>> virtualWindows;

    NativeWindow() {}

    virtual void recreateSwapChain();

    virtual void destroySwapChain();
    virtual void destroySurface();

  public:
    virtual ~NativeWindow();
    virtual void draw();

    void addVirtualWindow(std::shared_ptr<VirtualWindow> virtualWindow);

    // Getters ----------
    const vk::SwapchainKHR getSwapChain() const;
    const vk::Format getSwapChainFormat() const;
    const vk::Extent2D getSwapChainExtent() const;
    const std::vector<vk::Image> &getSwapChainImages() const;
    const uint32_t getCurrentFrameIndex() const;
    const std::vector<std::shared_ptr<VirtualWindow>> &
    getVirtualWindows() const;
    const std::shared_ptr<RenderTarget> &getRenderTarget();

    // Setters ----------
    void setRenderTarget(std::shared_ptr<RenderTarget> renderTarget);
};
} // namespace ikura