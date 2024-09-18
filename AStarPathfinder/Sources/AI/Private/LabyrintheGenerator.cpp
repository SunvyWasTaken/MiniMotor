
#include "LabyrintheGenerator.h"
#include "Terrain.h"

#include <iostream>
#include <random>

std::default_random_engine rGen;
using intRand = std::uniform_int_distribution<int>;

void LabyrintheGenerator::GenerateLabyrinthe(IWorld* World)
{
	bool MazeComplete = false;
	while (!MazeComplete)
	{
		std::map<IVec2, Cell*> CellMap;
		World->GetCellMap(CellMap);

		std::vector<Wall*> WallList;
		World->GetWallList(WallList);

		intRand RandomBorder(0, WallList.size() - 1);
		int CurrentIndex = RandomBorder(rGen);
		Wall* TargetWall = WallList[CurrentIndex];

		if (TargetWall->IsLocked)
		{
			continue;
		}

		std::array<Cell*, 2> CellNeighboor;
		if (!Get2Neighboor(TargetWall, CellMap, CellNeighboor))
		{
			continue;
		}

		if (CellNeighboor[0]->CurrentValue == CellNeighboor[1]->CurrentValue)
		{
			continue;
		}

		if (Cell* CurrentCell = World->SetCellAt(World->m_WallHead + CurrentIndex))
		{
			Cell* ReferentCell = CellNeighboor[0];

			CurrentCell->Neighbors.push_back(CellNeighboor[0]);
			CurrentCell->Neighbors.push_back(CellNeighboor[1]);
			CurrentCell->SetValue(ReferentCell->CurrentValue);

			CellNeighboor[0]->Neighbors.push_back(CurrentCell);
			CellNeighboor[1]->Neighbors.push_back(CurrentCell);

			// End the loop if all the cell have the same value.
			for (const auto& [key, cell] : CellMap)
			{
				MazeComplete = true;
				if (ReferentCell->CurrentValue != cell->CurrentValue)
				{
					MazeComplete = false;
					break;
				}
			}
			if (MazeComplete)
			{
				std::cout << "Maze Complete!! " << std::endl;
				return;
			}
		}
	}
}

bool LabyrintheGenerator::Get2Neighboor(const Wall* CurrentWall, std::map<IVec2, Cell*> CellList, std::array<Cell*, 2>& CellNeighboor)
{
	int CurrentIndex = 0;
	const std::array<IVec2, 4> offsets = { IVec2{0, 1}, IVec2{1, 0}, IVec2{0, -1}, IVec2{-1, 0} };
	for (const IVec2& offset : offsets)
	{
		IVec2 checkLocation = CurrentWall->Location + offset;
		auto it = CellList.find(checkLocation);

		if (it != CellList.end() && it->second->IsCell())
		{
			if (CurrentIndex <= 1)
			{
				CellNeighboor[CurrentIndex] = it->second;
			}
			CurrentIndex++;
		}
	}
	return CurrentIndex == 2 && CellNeighboor[0] != CellNeighboor[1];
}