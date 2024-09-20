#pragma once

#include "Define/CRTP.h"

#include "DrawableList.h"

template <typename Derived>
class GenericRender
{
public:

	virtual ~GenericRender() = default;

	CRTP_CALL(Init)
	CRTP_CALL(Draw)
	CRTP_CALL_ret(bool, IsWindowOpen)
	CRTP_CALL_OneParam(BufferFrame, class Entity*)
	CRTP_CALL(HandleEvent)
	CRTP_CALL(ClearWindow)
	CRTP_CALL(CloseWindow)
};
