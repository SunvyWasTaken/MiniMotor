#pragma once

#include "Event.h"
#include "Lights.h"
#include "Scene.h"
#include "LayersStack.h"

namespace Sunset
{
	struct OpenGL {};
	struct Vulkan {};

	using RenderType = std::variant<OpenGL, Vulkan>;
	using Renders = Typelist<class OpenGLRender, class VulkanRender>;

	template <typename T>
	class BasicRender;

	class OpenGLRender;
	class Camera;

	class MM_EXPORT BasicApp
	{

		using RenderPtr = std::unique_ptr<BasicRender<OpenGLRender>>;
		using ListLight = std::vector<Lights>;

	public:

		BasicApp();

		virtual ~BasicApp();

		virtual void Init() = 0;

		virtual void Update() = 0;

		void Run();

		void OnEvents(const Events& even);

		Scene* GetWorld();

		static BasicApp& Get() { return *AppPtr; }

		void* GetWindow();

		void PushLayer(class Layer* layer)
		{
			layerStack.PushLayer(layer);
		}

	protected:

		virtual const char* GetApplicationName() const { return "MiniMotor App"; }

	public:

		// todo : for the moment all light will be static.
		ListLight LightList;

		RenderPtr render;

	protected:

		float Deltatime;

	private:

		static BasicApp* AppPtr;

		Scene world;

		Camera* cam;

		LayerStack layerStack;

		class ImGuiLayer* imLayer;
	};
}
