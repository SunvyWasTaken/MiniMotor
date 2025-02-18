#pragma once

#include "BasicRender.h"
#include "Camera.h"
#include "Entity.h"
#include "Event.h"
#include "MesheComponent.h"
#include "TransformComponent.h"
#include "InputComponent.h"
#include "Meshes.h"
#include "Scene.h"

namespace Sunset
{
	template <typename TRender>
	class BasicApp
	{
		using Type = BasicApp<TRender>;
		using RenderType = BasicRender<TRender>;
		using RenderPtr = std::unique_ptr<RenderType>;

	public:
		BasicApp()
			: render(std::make_unique<TRender>(GetApplicationName(), FVec2{1280, 720}))
			, Deltatime(0.f)
		{
			render->BindInputCallback(std::bind(&Type::OnEvents, this, std::placeholders::_1));
			cam = world.SpawnEntity<Camera>();
		}

		virtual ~BasicApp() = default;

		virtual void Init() = 0;

		virtual void Update() = 0;

		void Run()
		{
			auto PreviousTime = std::chrono::steady_clock::now();

			Init();

			while (render->IsRunning())
			{
				auto CurrentTime = std::chrono::steady_clock::now();
				std::chrono::duration<float> deltatime = CurrentTime - PreviousTime;
				PreviousTime = CurrentTime;
				Deltatime = deltatime.count();

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

	protected:

		virtual const char* GetApplicationName() const { return "MiniMotor App"; }

	protected:

		float Deltatime;

	private:

		RenderPtr render;
		Scene world;
		Camera* cam;
	};
}
