// AStarPathfinder2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#define RENDERTYPE 1 // 0 = Console, 1 = SFML

#include "Vec2.h"

#include "AStarPathfinding.h"
#if RENDERTYPE == 0
#include "ConsoleRender.h"
using CurrentRender = ConsoleDraw;
#elif RENDERTYPE == 1
#include "SFMLRender.h"
using CurrentRender = SFMLDraw;
#endif
#include "Entitys.h"
#include "LabyrintheGenerator.h"
#include "Setting.h"
#include "Terrain.h"

int main()
{
	std::unique_ptr<IWorld> CurrentWorld = std::make_unique<IWorld>();
	CurrentRender CurrentRenderObj;
	CurrentRenderObj.World = CurrentWorld.get();
	CurrentRenderObj.Init();
	CurrentWorld->FillWorldGrid();
	Player* CurrentPlayer = CurrentWorld->SpawnEntity<Player>({1, 1});
	EndPoint* CurrentEndPoint = CurrentWorld->SpawnEntity<EndPoint>({39, 19});

	std::atomic<bool> IsLabyrintheGenerationDone = false;

	//PathFinderAlgo::AStarPathfinding(&CurrentWorld, CurrentPlayer->Location, CurrentEndPoint->Location);

	while (CurrentRenderObj.IsWindowOpen())
	{
		if (!IsLabyrintheGenerationDone)
		{
			LabyrintheGenerator::GenerateLabyrinthe(CurrentWorld.get(), IsLabyrintheGenerationDone);
		}
		CurrentRenderObj.HandleEvent();
		CurrentWorld->BufferFrameEntitys(CurrentRenderObj);
		CurrentRenderObj.Draw();
		CurrentRenderObj.ClearWindow();
	}
	CurrentRenderObj.CloseWindow();
}
