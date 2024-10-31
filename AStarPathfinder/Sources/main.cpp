#include "AStarPathfinding.h"
#include "MazeTerrain.h"
#include "MiniMotorApp.h"
#include "UIMaze.h"


int main()
{
	MiniMotorApp* CurrApp = MiniMotorApp::GetInstance();
	CurrApp->Init();

	// Start : Maze Generation
	SContainer* UiMaze = new MazeSlate();
	SButton MyConstructButton = SButton();
	SButton MyGenButton = SButton();
	SButton MyClearTerrain = SButton();
	SButton MyAstarPath = SButton();
	SButton MyAstarPath2 = SButton();
	SEditableText MyEditableText = SEditableText();
	

	MyGenButton.m_Text = "Generate Maze";
	MyClearTerrain.m_Text = "Clear Maze";
	MyAstarPath.m_Text = "A* Pathfinding";
	MyEditableText.m_Text = "Terrain Size";
	MyAstarPath2.m_Text = "Step by step";

	UiMaze->AddChild(
		&MyGenButton)
		.SetPadding<BottomRight>()
		.SetPosition({1920, 1080})
		.SetSize({500, 1080})
		;

	UiMaze->AddChild(&MyClearTerrain);
	UiMaze->AddChild(&MyEditableText);
	UiMaze->AddChild(&MyAstarPath);
	UiMaze->AddChild(&MyAstarPath2);

	CurrApp->PushLayer(UiMaze);
	std::unique_ptr<MazeTerrain> Maze = std::make_unique<MazeTerrain>();
	CurrApp->SetWorld(Maze.get());

	Maze->SetMazeSize({ 6, 6 });

	PathFinderAlgo::AStarPathfinding pathfinding(Maze.get());

	MyGenButton.BindOnPressed(Maze.get(), &MazeTerrain::GenerateLabyrinthe);
	MyClearTerrain.BindOnPressed(Maze.get(), &MazeTerrain::ClearLabyrinthe);
	MyAstarPath.BindOnPressed(&pathfinding, &PathFinderAlgo::AStarPathfinding::operator());
	MyEditableText.BindOnPressed(Maze.get(), &MazeTerrain::SetMazeSize);
	MyAstarPath2.BindOnPressed(Maze.get(), &MazeTerrain::AlgoLabyrinthe);
	// End : Maze Generation

	CurrApp->Run();
	CurrApp->Shutdown();

	return EXIT_SUCCESS;
}
