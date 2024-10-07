// Copyright Shimmer Studios : All rights reserved.

#pragma once

namespace Side
{
	struct MM_API TopLeft {};
	struct MM_API TopRight {};
	struct MM_API BottomRight {};
	struct MM_API BottomLeft {};
}

using QuadSide = Typelist<Side::TopLeft, Side::TopRight, Side::BottomRight, Side::BottomLeft>;

