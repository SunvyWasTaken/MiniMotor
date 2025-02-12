#pragma once

#include "OpenGLRender.h"
#include "VulkanRender.h"
#include "Camera.h"
#include "Event.h"
#include "Meshes.h"
#include "Scene.h"

namespace
{
	// Todo : this should be temporary
	std::vector<Vertex> vertices = {
		// positions						// normals					// texture coords
		Vertex{FVec3{-0.5f, -0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{ 0.5f, -0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{ 0.5f,  0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{ 0.5f,  0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{-0.5f,  0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f, -0.5f},  FVec3{0.0f,  0.0f, -1.0f},  FVec2{0.0f, 0.0f}},

		Vertex{FVec3{-0.5f, -0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{0.0f, 0.0f}},
		Vertex{FVec3{ 0.5f, -0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{1.0f, 0.0f}},
		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{1.0f, 1.0f}},
		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{1.0f, 1.0f}},
		Vertex{FVec3{-0.5f,  0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{0.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f,  0.5f},  FVec3{0.0f,  0.0f, 1.0f},   FVec2{0.0f, 0.0f}},

		Vertex{FVec3{-0.5f,  0.5f,  0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{-0.5f,  0.5f, -0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f, -0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f, -0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{-0.5f, -0.5f,  0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{-0.5f,  0.5f,  0.5f}, FVec3{-1.0f,  0.0f,  0.0f},  FVec2{1.0f, 0.0f}},

		Vertex{FVec3{0.5f,  0.5f,  0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{0.5f,  0.5f, -0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{0.5f, -0.5f, -0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{0.5f, -0.5f, -0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{0.5f, -0.5f,  0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{0.5f,  0.5f,  0.5f},  FVec3{1.0f,  0.0f,  0.0f},  FVec2{1.0f, 0.0f}},

		Vertex{FVec3{-0.5f, -0.5f, -0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{ 0.5f, -0.5f, -0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{ 0.5f, -0.5f,  0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{ 0.5f, -0.5f,  0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{-0.5f, -0.5f,  0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{-0.5f, -0.5f, -0.5f},  FVec3{0.0f, -1.0f,  0.0f},  FVec2{0.0f, 1.0f}},

		Vertex{FVec3{-0.5f,  0.5f, -0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{0.0f, 1.0f}},
		Vertex{FVec3{ 0.5f,  0.5f, -0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{1.0f, 1.0f}},
		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{ 0.5f,  0.5f,  0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{1.0f, 0.0f}},
		Vertex{FVec3{-0.5f,  0.5f,  0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{0.0f, 0.0f}},
		Vertex{FVec3{-0.5f,  0.5f, -0.5f},  FVec3{0.0f,  1.0f,  0.0f},  FVec2{0.0f, 1.0f}}
	};
}

template <typename TRender>
class BasicApp
{
	using Type = BasicApp<TRender>;
	using RenderType = BasicRender<TRender>;
	using RenderPtr = std::unique_ptr<RenderType>;

public:
	BasicApp()
		: render(std::make_unique<TRender>())
		, cam(std::make_unique<Camera>())
		, Deltatime(0.f)
	{
		render->BindInputCallback(std::bind(&Type::OnEvents, this, std::placeholders::_1));
	}

	void Run()
	{
		auto PreviousTime = std::chrono::high_resolution_clock::now();
		Mesh CurrentCube(vertices);

		while (render->IsRunning())
		{
			auto CurrentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> deltatime = CurrentTime - PreviousTime;
			PreviousTime = CurrentTime;
			Deltatime = deltatime.count();

			render->BeginFrame();

			render->Draw(cam.get(), &CurrentCube);

			render->EndFrame();
		}
	}

	void OnEvents(const Events& even)
	{
		// Todo : Move elsewhere like in the camera directly. and make a Input Manager.
		float InputSpeed = 5.f * Deltatime;
		std::visit(Overloaded{
			[&](KeyEvent key)
			{
				FVec3 vec(0);
				if (key == 83)
				{
					vec += FVec3{0.f, 0.f, -1.f};
				}
				else if (key == 87)
				{
					vec += FVec3{ 0.f, 0.f, 1.f };
				}
				else if (key == 68)
				{
					vec += FVec3{ 1.f, 0.f, 0.f };
				}
				else if (key == 65)
				{
					vec += FVec3{ -1.f, 0.f, 0.f };
				}
				else if (key == 69)
				{
					vec += FVec3{ 0.f, 1.f, 0.f };
				}
				else if (key == 81)
				{
					vec += FVec3{ 0.f, -1.f, 0.f };
				}
				Normalize<FVec3> norm;
				vec = norm(vec);
				cam->UpdateLocation(vec * InputSpeed);
			},
			[&](MouseEvent mouse)
			{
				cam->ChangeRotation(mouse.x, mouse.y);
			}
			}, even);
		//std::visit([&](auto&& val){std::cerr << val << std::endl; }, even);
	}

private:

	RenderPtr render;
	Scene world;
	std::unique_ptr<Camera> cam;
	float Deltatime;
};

using OpenGLApp = BasicApp<OpenGLRender>;
using VulkanApp = BasicApp<VulkanRender>;

template <typename T>
void RunApp()
{
	std::unique_ptr<T> curr = std::make_unique<T>();
	curr->Run();
}
