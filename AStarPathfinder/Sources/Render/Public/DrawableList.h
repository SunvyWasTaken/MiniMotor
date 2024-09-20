
#pragma once

#include "Quad2D.h"
#include "VertexArray2D.h"

#include <variant>
#include <vector>

using MDrawable = std::variant<FQuad2D, VertexArray2D>;

using MDrawableList = std::vector<MDrawable>;
