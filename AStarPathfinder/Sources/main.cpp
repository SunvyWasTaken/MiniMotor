// AStarPathfinder2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "World.h"

#include "AStarPathfinding.h"
#include "Entitys.h"
#include "MazeTerrain.h"
#include "MiniMotorApp.h"
#include "UIMaze.h"


#include <iostream>

int main()
{
	std::unique_ptr<MiniMotorApp> CurrApp = std::make_unique<MiniMotorApp>();
	CurrApp->Init();

	// Start : Maze Generation
	SContainer* UiMaze = new MazeSlate();
	SButton MyConstructButton = SButton();
	SButton MyGenButton = SButton();
	SButton MyClearTerrain = SButton();
	SButton MyAstarPath = SButton();
	SEditableText MyEditableText = SEditableText();
	
	MyConstructButton.m_Text = "Construct Maze";
	MyGenButton.m_Text = "Generate Maze";
	MyClearTerrain.m_Text = "Clear Maze";
	MyAstarPath.m_Text = "A* Pathfinding";
	MyEditableText.m_Text = "Terrain Size";

	UiMaze->AddChild(
		&MyGenButton)
		.SetPadding<BottomRight>()
		.SetPosition({1920, 1080})
		.SetSize({500, 1080})
		;

	UiMaze->AddChild(&MyConstructButton);
	UiMaze->AddChild(&MyClearTerrain);
	UiMaze->AddChild(&MyEditableText);
	UiMaze->AddChild(&MyAstarPath);

	CurrApp->PushLayer(UiMaze);
	std::unique_ptr<World> CurrentWorld = std::make_unique<World>();
	CurrApp->SetWorld(CurrentWorld.get());

	MazeTerrain* Maze = new MazeTerrain();
	CurrentWorld->Entities.push_back(Maze);
	Maze->SetMazeSize({ 250, 250 });

	PathFinderAlgo::AStarPathfinding pathfinding(Maze);

	MyConstructButton.BindOnPressed(Maze, &MazeTerrain::RegenerateLabyrinthe);
	MyGenButton.BindOnPressed(Maze, &MazeTerrain::GenerateLabyrinthe);
	MyClearTerrain.BindOnPressed(Maze, &MazeTerrain::ClearLabyrinthe);
	MyAstarPath.BindOnPressed(&pathfinding, &PathFinderAlgo::AStarPathfinding::operator());
	MyEditableText.BindOnPressed(Maze, &MazeTerrain::SetMazeSize);
	// End : Maze Generation

	CurrApp->Run();

	// Clean up
	delete Maze;

	CurrApp->Shutdown();

	return 0;
}
