// Copyright Shimmer Studios : All rights reserved.

#include "GenericRender.h"
#include "MiniMotorApp.h"

EventsCallback::EventsCallback()
	: m_Callback(nullptr)
	, m_App(nullptr)
{
}

void EventsCallback::Bind(MiniMotorApp* app, const EventCallbackType& func)
{
	m_App = app;
	m_Callback = func;
}

bool EventsCallback::operator()(const Events& event)
{
	ensure(m_Callback);
	return (m_App->*m_Callback)(event);
}
