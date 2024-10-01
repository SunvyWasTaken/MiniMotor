#include "GenericRender.h"

EventsCallback::EventsCallback()
{
}

void EventsCallback::Bind(const EventCallbackType& func)
{
	m_Callback = func;
}

void EventsCallback::operator()(const Events& event)
{
	ensure(m_Callback);
	m_Callback(event);
}
