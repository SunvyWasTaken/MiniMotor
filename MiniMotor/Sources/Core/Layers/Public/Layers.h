#pragma once

#include "Event.h"

namespace Sunset
{
	class Layer
	{
	public:
		explicit Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(const Events& ev);

		inline const std::string& operator()() const { return m_Name; }
	private:
		std::string m_Name;
	};
}
