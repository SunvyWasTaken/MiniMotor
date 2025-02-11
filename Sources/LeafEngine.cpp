// LeafEngine.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "OpenGLRender.h"
#include "Camera.h"

template <typename TRender>
class BasicApp
{
    using RenderType = TRender;
    using RenderTypePtr = RenderType*;
    using RenderPtr = std::unique_ptr<BasicRender<RenderType>>;

public:
    BasicApp()
        : render(std::make_unique<RenderType>())
    {}

    void Run()
    {
        std::unique_ptr<Camera> cam = std::make_unique<Camera>();
        auto PreviousTime = std::chrono::high_resolution_clock::now();
        while (render->IsRunning())
        {
            auto CurrentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> deltatime = CurrentTime - PreviousTime;
            PreviousTime = CurrentTime;

            render->Run(cam.get());
        }
    }

private:

    RenderPtr render;
};

using App = BasicApp<OpenGLRender>;
using AppPtr = std::unique_ptr<App>;

int main()
{
    AppPtr curr = std::make_unique<App>();
    curr->Run();
}

