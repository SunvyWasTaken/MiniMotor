#include "Application.h"
#include "BasicRender.h"
#include "Camera.h"
#include "Entity.h"
#include "ImGuiLayer.h"
#include "InputComponent.h"
#include "MesheComponent.h"
#include "Meshes.h"
#include "OpenGLRender.h"
#include "TransformComponent.h"

Sunset::BasicApp* Sunset::BasicApp::AppPtr = nullptr;

namespace Sunset
{
	BasicApp::BasicApp()
		: render(std::make_unique<OpenGLRender>(GetApplicationName(), FVec2{1280, 720}))
		, Deltatime(0.f)
	{
		AppPtr = this;
		render->BindInputCallback(std::bind(&BasicApp::OnEvents, this, std::placeholders::_1));
		cam = world.SpawnEntity<Camera>();

		imLayer = new ImGuiLayer();
		PushLayer(imLayer);
	}

	BasicApp::~BasicApp()
	{
	}

	void BasicApp::Run()
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

			Update();

			world.Update(Deltatime);

			// Start rendering maybe it's going to be in another thread oO!
			render->BeginFrame();

			for (auto& layer : layerStack)
			{
				layer->OnUpdate();
			}

			auto views = world.entitys.view<MeshComponent, TransformComponent>();
			for (auto curr : views)
			{
				MeshComponent& currMesh = world.entitys.get<MeshComponent>(curr);
				TransformComponent& currTrans = world.entitys.get<TransformComponent>(curr);
				render->Draw(cam, currMesh(), currTrans());
			}

			imLayer->Begin();
			for (auto& layer : layerStack)
			{
				layer->OnImGuiRender();
			}
			imLayer->End();

			render->EndFrame();
		}
	}

	void BasicApp::OnEvents(const Events& even)
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

	Scene* BasicApp::GetWorld()
	{
		return &world;
	}

	void* BasicApp::GetWindow()
	{
		return render->GetWindow();
	}
}