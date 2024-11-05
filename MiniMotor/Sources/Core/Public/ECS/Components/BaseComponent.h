// Copyright Shimmer Studios : All rights reserved.

#pragma once
#include "Events/Events.h"

// BaseComponent is a base class for all components
// It will be used to check if a class is a component
class BaseComponent
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent() = default;
};

using OnClickEvent = std::function<void(bool)>;

class InputComponent : public BaseComponent
{
public:
	InputComponent() = default;
	virtual ~InputComponent() = default;

	void AddCallback(const KeyCode key, const OnClickEvent& callback)
	{
		callbacks.emplace(key, callback);
	}

private:

	std::map<KeyCode, OnClickEvent> callbacks;

	friend class World;
};

