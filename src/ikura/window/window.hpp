#pragma once

#include <memory>
#include <string>

#include <vulkan/vulkan.hpp>

#include "../renderComponent/renderContent.hpp"
#include "../renderComponent/renderTarget.hpp"

namespace ikura {
class Window {
  protected:
    Window() {}

    std::shared_ptr<RenderEngine> renderEngine;

    int width, height;
    std::string name;
    int numOfFrames = 3;

    bool resourceDestroyed = false;

    std::shared_ptr<RenderContent> renderContent;

  public:
    virtual ~Window();
    virtual bool closed();
    virtual void destroyResources();

    // Getters ----------
    const int getNumOfFrames() const;
    const vk::DescriptorSetLayout getDescriptorSetLayout() const;
    const int getWidth() const;
    const int getHeight() const;
    const std::shared_ptr<RenderContent> &getRenderContent();

    // Setters ----------
    void setRenderContent(std::shared_ptr<RenderContent> renderContent);
};
} // namespace ikura