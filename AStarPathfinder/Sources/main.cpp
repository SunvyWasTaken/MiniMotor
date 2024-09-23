// AStarPathfinder2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#define RENDERTYPE 1 // 0 = Console, 1 = SFML

#include "World.h"

#if RENDERTYPE == 0
#include "ConsoleRender.h"
using CurrentRender = ConsoleRender;
#elif RENDERTYPE == 1
#include "SFMLRender.h"
using CurrentRender = SFMLRender;
#elif RENDERTYPE == 2
#include "OpenGLRender.h"
using CurrentRender = OpenGLRender;
#endif

#include "Entitys.h"
#include "MazeTerrain.h"

int main()
{
	std::unique_ptr<World> CurrentWorld = std::make_unique<World>();
	std::unique_ptr<GenericRender<CurrentRender>> CurrentRenderObj = std::make_unique<CurrentRender>();

	MazeTerrain* Maze = new MazeTerrain();

	CurrentWorld->Entities.push_back(Maze);
	Maze->GenerateTerrain({200, 200});

	std::atomic<bool> IsGenerationDone = false;
	CurrentRenderObj->Init();
	// Todo : Changer pour que ce soit tant que l'application est ouverte.
	while (CurrentRenderObj->IsWindowOpen())
	{
		// Todo : Add PreRender function for class like ImGuiRender who need a ImGuiNewFrame() call.
		if (!IsGenerationDone.load(std::memory_order_relaxed))
		{
			Maze->GenerateLabyrinthe(IsGenerationDone);
		}
		CurrentRenderObj->HandleEvent();
		CurrentWorld->BufferFrameEntitys(*CurrentRenderObj);
		CurrentRenderObj->Draw();
		CurrentRenderObj->ClearWindow();
	}
	delete Maze;
	// Todo : Ici tu close la fenêtre.
	CurrentRenderObj->CloseWindow();
}
