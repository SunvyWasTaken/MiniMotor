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
	IWorld CurrentWorld;
	CurrentRender CurrentRender;
	CurrentRender.World = &CurrentWorld;
	CurrentRender.Init();
	CurrentWorld.FillWorldGrid();
	Player* CurrentPlayer = CurrentWorld.SpawnEntity<Player>({1, 1});
	EndPoint* CurrentEndPoint = CurrentWorld.SpawnEntity<EndPoint>({39, 19});

	LabyrintheGenerator::GenerateLabyrinthe(&CurrentWorld);

	PathFinderAlgo::AStarPathfinding(&CurrentWorld, CurrentPlayer->Location, CurrentEndPoint->Location);

	while (CurrentRender.IsWindowOpen())
	{
		CurrentWorld.BufferFrameEntitys(CurrentRender);
		CurrentRender.Draw();
		CurrentRender.ClearWindow();
	}
	CurrentRender.CloseWindow();
}
