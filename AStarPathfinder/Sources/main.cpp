// AStarPathfinder2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "World.h"

#include "Entitys.h"
#include "MazeTerrain.h"

#include "MiniMotorApp.h"

#include <iostream>

int main()
{
	std::unique_ptr<MiniMotorApp> CurrApp = std::make_unique<MiniMotorApp>();
	CurrApp->Init();

	std::unique_ptr<World> CurrentWorld = std::make_unique<World>();
	CurrApp->SetWorld(CurrentWorld.get());

	MazeTerrain* Maze = new MazeTerrain();
	CurrentWorld->Entities.push_back(Maze);
	CHECK_PERF(Maze->GenerateTerrain({ 400, 400 }))

	CHECK_PERF(Maze->GenerateLabyrinthe())
	CurrApp->Run();
	delete Maze;

	CurrApp->Shutdown();

	return 0;
}
