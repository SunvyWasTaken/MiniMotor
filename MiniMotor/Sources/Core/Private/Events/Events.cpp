#include "Events/Events.h"

namespace MEvents
{
	OnWindowClose::OnWindowClose()
	{
	}

	OnWindowResize::OnWindowResize(const ScreenCoord& screenSize)
		: m_size(screenSize)
	{
	}

	OnWindowFocus::OnWindowFocus()
	{
	}

	OnWindowLostFocus::OnWindowLostFocus()
	{
	}

	OnWindowMoved::OnWindowMoved()
	{
	}

	OnAppTick::OnAppTick(const double deltatime)
		: m_deltatime(deltatime)
	{
	}

	OnAppUpdate::OnAppUpdate()
	{
	}

	OnAppRender::OnAppRender()
	{
	}

	OnKeyPressed::OnKeyPressed(const KeyCode& key)
		: m_key(key)
	{
	}

	OnKeyReleased::OnKeyReleased(const KeyCode& key)
		: m_key(key)
	{
	}

	OnMouseButtonPressed::OnMouseButtonPressed(uint8_t button)
		: m_Button(button)
	{
	}

	OnMouseButtonReleased::OnMouseButtonReleased(uint8_t button)
		: m_Button(button)
	{
	}

	OnMouseMoved::OnMouseMoved(const ScreenCoord& pos)
		: m_pos(pos)
	{
	}

	OnMouseScrolled::OnMouseScrolled(double delta)
		: m_delta(delta)
	{
	}

}
