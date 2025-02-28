#pragma once

#include "Camera.h"
#include "Event.h"
#include "LayersStack.h"
#include "WindowPC.h"

namespace Sunset
{
	class ImGuiLayer;

	class MM_API BasicApp
	{

		using Win = Window<WindowPC>;

	public:

		BasicApp();

		virtual ~BasicApp();

		virtual void Init() = 0;

		virtual void Update() = 0;

		void Run();

		void OnEvents(const Events& even);

		void PushLayer(class Layer* layer);

		inline Win& GetWindow() { return *m_Window; };

		inline static BasicApp& Get() { return *AppPtr; }

		// todo : TMP
		Camera* GetCam();

	private:

		std::unique_ptr<Win> m_Window;

		static BasicApp* AppPtr;

		LayerStack layerStack;
	};
}
