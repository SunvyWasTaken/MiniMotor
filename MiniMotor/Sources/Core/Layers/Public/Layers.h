#pragma once

#include "Event.h"

namespace Sunset
{
	class MM_API Layer
	{
	public:
		explicit Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnImGuiRender();

		inline const std::string& operator()() const { return m_Name; }
	private:
		std::string m_Name;
	};
}
