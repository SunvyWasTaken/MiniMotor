#pragma once

#include "Event.h"

namespace Sunset
{
	using EventCallBackFn = std::function<void(const Events&)>;

	struct WindowData
	{
		std::string Title;
		uint32_t Width, Height;

		EventCallBackFn EventCallBack;

		WindowData(const std::string& _title = "Sunset Engine",
			uint32_t _width = 1280,
			uint32_t _height = 720);
	};

	template <typename Derived>
	class Window
	{
		using DerivedPtr = Derived*;
	public:

		Window(const WindowData& props) {}

		virtual ~Window() {}

		CRTP(OnUpdate)

		uint32_t GetWidth() const { return m_Data.Width; }

		uint32_t GetHeight() const { return m_Data.Height; }

		CRTP_VAR(SetEventCallBack)

		CRTP_VAR(SetVSync)
		RET_CONST_CRTP(IsVSync, bool)

		RET_CONST_CRTP(GetNativeWindow, void*)

	protected:

		WindowData m_Data;
	};
}
