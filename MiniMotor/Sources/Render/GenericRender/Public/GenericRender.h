// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "Define/CRTP.h"
#include "DrawableList.h"
#include "Events/Events.h"

using EventsCallback = std::function<bool(const Events&)>;

template <typename Derived>
class MM_EXPORT GenericRender
{
public:

	virtual ~GenericRender() = default;

	CRTP(Init)
	CRTP(Update)
	CRTP_ret(bool, IsWindowOpen)
	CRTP_Params(DrawObject)
	CRTP(CloseWindow)
	CRTP_Params(BindEvents)
};
