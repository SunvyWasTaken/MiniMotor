#include "AStarPathfinding.h"

void PathFinderAlgo::AStarPathfinding(IWorld* World, IVec2 Start, IVec2 End)
{
	std::map<IVec2, Cell*> CellMap;
	World->GetCellMap(CellMap);

	std::vector<Cell*> OpenList;
	std::vector<Cell*> ClosedList;

	Cell* StartCell = CellMap[Start];
	Cell* EndCell = CellMap[End];

	OpenList.push_back(StartCell);

	while (!OpenList.empty())
	{
		Cell* CurrentCell = OpenList[0];
		for (size_t i = 1; i < OpenList.size(); ++i)
		{
			if ((OpenList[i]->Location - End).length() < (CurrentCell->Location - End).length())
			{
				CurrentCell = OpenList[i];
			}
		}

		OpenList.erase(std::remove(OpenList.begin(), OpenList.end(), CurrentCell), OpenList.end());
		ClosedList.push_back(CurrentCell);

		if (CurrentCell == EndCell)
		{
			// Path found
			for (auto tmp : ClosedList)
			{
				tmp->Character = ".";
			}
			return;
		}

		for (Cell* Neighboor : CurrentCell->Neighbors)
		{
			if (std::find(ClosedList.begin(), ClosedList.end(), Neighboor) != ClosedList.end())
			{
				continue;
			}

			int NewCost = static_cast<int>((CurrentCell->Location - End).length() + 1);
			if (NewCost < (Neighboor->Location - End).length() || std::find(OpenList.begin(), OpenList.end(), Neighboor) == OpenList.end())
			{
				if (std::find(OpenList.begin(), OpenList.end(), Neighboor) == OpenList.end())
				{
					OpenList.push_back(Neighboor);
				}
			}
		}
	}
};
