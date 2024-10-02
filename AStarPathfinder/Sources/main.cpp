// AStarPathfinder2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "World.h"

#include "Entitys.h"
#include "MazeTerrain.h"
#include "UIMaze.h"

#include "MiniMotorApp.h"

#include <iostream>

int main()
{
	std::unique_ptr<MiniMotorApp> CurrApp = std::make_unique<MiniMotorApp>();
	CurrApp->Init();

	// Start : Maze Generation

	SContainer* UiMaze = new MazeSlate();
	SButton MyGenButton = SButton();
	SButton MyClearTerrain = SButton();
	MyGenButton.m_Text = "Generate Maze";
	MyClearTerrain.m_Text = "Clear Maze";

	UiMaze->AddChild(
		&MyGenButton)
		.SetPadding<BottomRight>()
		.SetPosition({1920, 1080})
		.SetSize({500, 1080})
		;
	UiMaze->AddChild(&MyClearTerrain);

	CurrApp->PushLayer(UiMaze);
	std::unique_ptr<World> CurrentWorld = std::make_unique<World>();
	CurrApp->SetWorld(CurrentWorld.get());

	MazeTerrain* Maze = new MazeTerrain();
	CurrentWorld->Entities.push_back(Maze);
	Maze->SetMazeSize({ 300, 300 });
	//CHECK_PERF(Maze->GenerateLabyrinthe())

	MyGenButton.BindOnPressed(Maze, &MazeTerrain::GenerateLabyrinthe);
	MyClearTerrain.BindOnPressed(Maze, &MazeTerrain::ClearLabyrinthe);
	// End : Maze Generation

	CurrApp->Run();

	// Clean up
	delete Maze;

	CurrApp->Shutdown();

	return 0;
}
