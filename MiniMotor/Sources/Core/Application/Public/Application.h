#pragma once

#include "BasicRender.h"
#include "Camera.h"
#include "Entity.h"
#include "Event.h"
#include "InputComponent.h"
#include "Layers.h"
#include "LayersStack.h"
#include "MesheComponent.h"
#include "Meshes.h"
#include "Scene.h"
#include "TransformComponent.h"

namespace Sunset
{
	template <typename TRender>
	class BasicApp
	{
		using Type = BasicApp<TRender>;
		using RenderType = BasicRender<TRender>;
		using RenderPtr = std::unique_ptr<RenderType>;

		using ListLight = std::vector<Lights>;

	public:

		static BasicApp<TRender>* AppPtr;

		BasicApp()
			: render(std::make_unique<TRender>(GetApplicationName(), FVec2{1280, 720}))
			, Deltatime(0.f)
		{
			if (AppPtr)
			{
				throw std::exception(std::runtime_error("App already exist"));
				return;
			}
			AppPtr = this;
			render->BindInputCallback(std::bind(&Type::OnEvents, this, std::placeholders::_1));
			cam = world.SpawnEntity<Camera>();
		}

		virtual ~BasicApp()
		{
			AppPtr = nullptr;
		}

		virtual void Init() = 0;

		virtual void Update() = 0;

		void PushLayer(Layer* layer)
		{
			m_LayerStack.PushLayer(layer);
		}

		void PushOverlay(Layer* layer)
		{
			m_LayerStack.PushOverlay(layer);
		}

		void Run()
		{
			auto PreviousTime = std::chrono::steady_clock::now();

			Init();

			// todo : change the way light info is send cuz right now they will be copy to the render. i don't want to do such a thing.
			for (auto& currLight : LightList)
			{
				render->DrawLight(&currLight);
			}

			while (render->IsRunning())
			{
				auto CurrentTime = std::chrono::steady_clock::now();
				std::chrono::duration<float> deltatime = CurrentTime - PreviousTime;
				PreviousTime = CurrentTime;
				Deltatime = deltatime.count();

				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate();
				}

				Update();

				// Start rendering maybe it's going to be in another thread oO!
				render->BeginFrame();
				auto views = world.entitys.view<MeshComponent, TransformComponent>();
				for (auto curr : views)
				{
					MeshComponent& currMesh = world.entitys.get<MeshComponent>(curr);
					TransformComponent& currTrans = world.entitys.get<TransformComponent>(curr);
					render->Draw(cam, currMesh(), currTrans());
				}
				render->EndFrame();
			}
		}

		void OnEvents(const Events& even)
		{
			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
			{
				(*--it)->OnEvent(even);
			}

			auto views = world.entitys.view<InputComponent>();
			for (auto curr : views)
			{
				InputComponent& currInput = world.entitys.get<InputComponent>(curr);
				currInput.OnEvent(even, Deltatime);
			}
			// Todo : Move elsewhere like in the camera directly. and make a Input Manager.
			float InputSpeed = 200.f * Deltatime;
			std::visit(Overloaded{
				[&](KeyEvent key)
				{
					if (key == 256)
					{
						render->CloseWindow();
						return;
					}
				},
				[&](MouseEvent mouse)
				{
					cam->ChangeRotation(mouse.x, mouse.y);
				}
				}, even);
		}

		Scene* GetWorld() { return &world; }

		static void* GetWindow() { return AppPtr->render->GetWindow(); }

	protected:

		virtual const char* GetApplicationName() const { return "MiniMotor App"; }

	public:

		// todo : for the moment all light will be static.
		ListLight LightList;

	protected:

		float Deltatime;

	private:

		RenderPtr render;
		Scene world;
		Camera* cam;

		LayerStack m_LayerStack;
	};
}

template <typename T>
Sunset::BasicApp<T>* Sunset::BasicApp<T>::AppPtr = nullptr;
