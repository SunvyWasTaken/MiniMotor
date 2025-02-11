// LeafEngine.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "OpenGLRender.h"
#include "Camera.h"
#include "Event.h"

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
    {
        render->BindInputCallback(std::bind(&Type::OnEvents, this, std::placeholders::_1));
    }

    void Run()
    {
        auto PreviousTime = std::chrono::high_resolution_clock::now();
        while (render->IsRunning())
        {
            auto CurrentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> deltatime = CurrentTime - PreviousTime;
            PreviousTime = CurrentTime;
            Deltatime = deltatime.count();

            render->Run(cam.get());
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
    std::unique_ptr<Camera> cam;
    float Deltatime;
};

using App = BasicApp<OpenGLRender>;
using AppPtr = std::unique_ptr<App>;

int main()
{
    AppPtr curr = std::make_unique<App>();
    curr->Run();
}

