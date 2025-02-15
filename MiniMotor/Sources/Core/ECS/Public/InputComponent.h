#pragma once

#include "Event.h"

namespace Sunset
{
	class MM_API InputComponent
	{
		using CallbackFunction = std::function<void(float)>;
		using InputCallbacks = std::map<int, CallbackFunction>;
		
	public:
		void Bind(int key, const CallbackFunction& func);

	private:

		void OnEvent(const Events& even, float deltatime);

	private:

		InputCallbacks functions;

		template <typename T>
		friend class BasicApp;
	};
}
