#pragma once

#include "glm/glm.hpp"
#include "base/System.h"
#include <functional>

namespace glowy3d
{

void start(std::function<void()> init, std::function<void()> update);

}
