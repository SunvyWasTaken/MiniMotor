#pragma once

#include "Define/CRTP.h"
#include "DrawableList.h"
#include "Events/Events.h"

class MM_API EventsCallback
{
	using EventCallbackType = std::function<void(const Events&)>;
public:
	EventsCallback();

	void Bind(const EventCallbackType& func);

	void operator()(const Events& event);

private:
	EventCallbackType m_Callback;
};

template <typename Derived>
class MM_EXPORT GenericRender
{
public:

	virtual ~GenericRender() = default;

	CRTP_CALL(Init)
	CRTP_CALL(Draw)
	CRTP_CALL_ret(bool, IsWindowOpen)
	CRTP_CALL_OneParam(BufferFrame, class Entity*)
	CRTP_CALL(HandleEvents)
	CRTP_CALL(ClearWindow)
	CRTP_CALL(CloseWindow)

	EventsCallback EventCall;
};
