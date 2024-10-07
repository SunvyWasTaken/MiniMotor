// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "Define/CRTP.h"
#include "DrawableList.h"
#include "Events/Events.h"

class MiniMotorApp;

class MM_API EventsCallback
{
	using EventCallbackType = bool(MiniMotorApp::*)(const Events&);
public:
	EventsCallback();

	void Bind(MiniMotorApp* app, const EventCallbackType& func);

	bool operator()(const Events& event);

private:
	EventCallbackType m_Callback;
	MiniMotorApp* m_App;
};

template <typename Derived>
class MM_EXPORT GenericRender
{
public:

	virtual ~GenericRender() = default;

	CRTP_CALL(Init)
	CRTP_CALL(Update)
	CRTP_CALL(Draw)
	CRTP_CALL_ret(bool, IsWindowOpen)
	CRTP_CALL_OneParam(BufferFrame, const VertexArray2D&)
	CRTP_CALL(HandleEvents)
	CRTP_CALL(ClearWindow)
	CRTP_CALL(CloseWindow)

	// Todo : Tmp solution change for the Slate
	CRTP_CALL_OneParam(DrawSlate, class SContainer*)

	EventsCallback EventCall;
};
