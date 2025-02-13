#pragma once

#include "BasicRender.h"
#include "Camera.h"
#include "Entity.h"
#include "Event.h"
#include "MesheComponent.h"
#include "Meshes.h"
#include "Scene.h"

template <typename TRender>
class BasicApp
{
	using Type = BasicApp<TRender>;
	using RenderType = BasicRender<TRender>;
	using RenderPtr = std::unique_ptr<RenderType>;

public:
	BasicApp()
		: render(std::make_unique<TRender>(GetApplicationName(), FVec2{1280, 720}))
		, cam(std::make_unique<Camera>())
		, Deltatime(0.f)
	{
		render->BindInputCallback(std::bind(&Type::OnEvents, this, std::placeholders::_1));
	}

	virtual ~BasicApp() = default;

	virtual void Init() = 0;

	virtual void Update() = 0;

	void Run()
	{
		auto PreviousTime = std::chrono::high_resolution_clock::now();

		Init();

		while (render->IsRunning())
		{
			auto CurrentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> deltatime = CurrentTime - PreviousTime;
			PreviousTime = CurrentTime;
			Deltatime = deltatime.count();

			Update();

			// Start rendering maybe it's going to be in another thread oO!
			render->BeginFrame();
			auto views = world.entitys.view<MeshComponent>();
			for (auto curr : views)
			{
				MeshComponent& currComponent = world.entitys.get<MeshComponent>(curr);
				render->Draw(cam.get(), currComponent());
			}
			render->EndFrame();
		}
	}

	void OnEvents(const Events& even)
	{
		// Todo : Move elsewhere like in the camera directly. and make a Input Manager.
		//float InputSpeed = 10.f * Deltatime;
		float InputSpeed = 0.1f;
		std::visit(Overloaded{
			[&](KeyEvent key)
			{
				if (key == 256)
				{
					render->CloseWindow();
					return;
				}

				FVec3 vec = FVec3(0, 0, 0);
				if (key == 83)
				{
					vec += FVec3{0.f, 0.f, -1.f};
				}
				if (key == 87)
				{
					vec += FVec3{ 0.f, 0.f, 1.f };
				}
				if (key == 68)
				{
					vec += FVec3{ 1.f, 0.f, 0.f };
				}
				if (key == 65)
				{
					vec += FVec3{ -1.f, 0.f, 0.f };
				}
				if (key == 69)
				{
					vec += FVec3{ 0.f, 1.f, 0.f };
				}
				if (key == 81)
				{
					vec += FVec3{ 0.f, -1.f, 0.f };
				}
				Normalize<FVec3> norm;
				vec = norm(vec);
				cam->UpdateLocation(vec * InputSpeed);
				std::visit([&](auto&& val){std::cerr << val << ", vec : " << vec.x << ", y:" << vec.y << ", z:" << vec.z << std::endl; }, even);
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

private:

	RenderPtr render;
	Scene world;
	std::unique_ptr<Camera> cam;
	float Deltatime;
};
