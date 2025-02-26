#pragma once

#include "Event.h"
#include "Lights.h"
#include "LayersStack.h"
#include "WindowPC.h"

namespace Sunset
{
	class ImGuiLayer;

	class MM_EXPORT BasicApp
	{
		using ListLight = std::vector<Lights>;
		using Win = Window<WindowPC>;

	public:

		BasicApp();

		virtual ~BasicApp();

		virtual void Init() = 0;

		virtual void Update() = 0;

		void Run();

		void OnEvents(const Events& even);

		void PushLayer(class Layer* layer)
		{
			layerStack.PushLayer(layer);
		}

		inline Win& GetWindow() { return *m_Window; }

		inline static BasicApp& Get() { return *AppPtr; }

	private:

		std::unique_ptr<Win> m_Window;

		bool b_IsWinOpen;

		LayerStack layerStack;

		ImGuiLayer* imLayer;

		static BasicApp* AppPtr;
	};
}
