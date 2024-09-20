
#pragma once

#include "Quad2D.h"
#include "VertexArray2D.h"

#include <map>
#include <string>
#include <variant>
#include <vector>

using MDrawable = std::variant<FQuad2D, VertexArray2D>;

using MVectorDrawable = std::vector<MDrawable>;

using MDrawableList = std::map<std::string, MDrawable>;
