#pragma once

#include "Layers.h"

namespace Sunset
{
	class MM_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() override;
		
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(const Events& even);
	};
}
