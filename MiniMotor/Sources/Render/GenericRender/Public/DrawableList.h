// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "Geometry/Quad2D.h"
#include "Geometry/VertexArray2D.h"

using MDrawable = std::variant<FQuad2D, VertexArray2D>;

using MVectorDrawable = std::vector<MDrawable>;

using MDrawableList = std::map<std::string, MDrawable>;
