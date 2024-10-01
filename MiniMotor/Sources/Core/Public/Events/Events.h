
#pragma once

#include "CoreMinimal.h"

namespace MEvents
{
	struct MM_API OnClose {};
	MAKE_STATE(OnResize)
	MAKE_STATE(OnFocus)
	MAKE_STATE(OnLostFocus)
	MAKE_STATE(OnMoved)
	MAKE_STATE(OnAppTick)
	MAKE_STATE(OnAppUpdate)
	MAKE_STATE(OnAppRender)
	MAKE_STATE(OnKeyPressed)
	MAKE_STATE(OnKeyReleased)
	MAKE_STATE(OnMouseButtonPressed)
	MAKE_STATE(OnMouseButtonReleased)
	MAKE_STATE(OnMouseMoved)
	MAKE_STATE(OnMouseScrolled)
}

using Events = std::variant<MEvents::OnClose
							, MEvents::OnResize
							, MEvents::OnFocus
							, MEvents::OnLostFocus
							, MEvents::OnMoved
							, MEvents::OnAppTick
							, MEvents::OnAppUpdate
							, MEvents::OnAppRender
							, MEvents::OnKeyPressed
							, MEvents::OnKeyReleased
							, MEvents::OnMouseButtonPressed
							, MEvents::OnMouseButtonReleased
							, MEvents::OnMouseMoved
							, MEvents::OnMouseScrolled>;
