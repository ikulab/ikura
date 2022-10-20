#pragma once

#include "ikuraConfig.h"

// Includes ----------
// Engine
#include "engine/appEngine.hpp"
#include "engine/renderEngine/renderEngine.hpp"

// Common header
#include "common/renderPrimitiveTypes.hpp"
#include "common/uniformBufferInfo.hpp"

// RenderComponents
#include "renderComponent/basic/basicRenderComponentProvider.hpp"
#include "renderComponent/basic/basicRenderContent.hpp"
#include "renderComponent/basic/basicRenderTarget.hpp"

// shapes
#include "shape/shapes.hpp"


// Definitions ----------
#define IKURA_RESOURCE_DIR ./
#ifdef __linux__
#define IKURA_RESOURCE_DIR ~/.local/share/ikura
#endif