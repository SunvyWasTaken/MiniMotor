
#include "Terrain.h"

#include "Vec2.h"

#include <memory>

IWorld::IWorld()
	: m_BorderHead(0)
	, m_WallHead((2 * GRID_SIZE_Y) + (2 * GRID_SIZE_X))
	, m_CellHead((GRID_SIZE_Y* GRID_SIZE_X * 0.75) + GRID_SIZE_Y + GRID_SIZE_X + 1)
{}

Cell* IWorld::SetCellAt(size_t Index)
{
	if (Index >= m_CellHead - 1)
	{
		return nullptr;
	}
	IVec2 TmpLoc = TerrainGrid[Index]->Location;
	--m_CellHead;
	TerrainGrid[Index].release();
	TerrainGrid[Index] = std::make_unique<Wall>(TerrainGrid[m_CellHead]->Location);
	TerrainGrid[m_CellHead] = std::make_unique<Cell>(TmpLoc);
	return static_cast<Cell*>(TerrainGrid[m_CellHead].get());
}

void IWorld::FillWorldGrid()
{
	size_t BorderHead = m_BorderHead;
	size_t WallHead = m_WallHead;
	size_t CellHead = m_CellHead;
	int CellValue = 0;
	for (size_t y = 0; y < GRID_SIZE_Y + 1; ++y)
	{
		for (size_t x = 0; x < GRID_SIZE_X + 1; ++x)
		{
			bool xTrue = x % 2 == 0;
			bool yTrue = y % 2 == 0;
			if (xTrue || yTrue)
			{
				if (y == 0 || y == GRID_SIZE_Y || x == 0 || x == GRID_SIZE_X)
				{
					TerrainGrid[BorderHead] = std::make_unique<Wall>(IVec2{ x, y });
					++BorderHead;
					continue;
				}
				else
				{
					TerrainGrid[WallHead] = std::make_unique<Wall>(IVec2{ x, y });
					if (xTrue && yTrue)
					{
						static_cast<Wall*>(TerrainGrid[WallHead].get())->IsLocked = true;
					}
					++WallHead;
				}
			}
			else
			{
				TerrainGrid[CellHead] = std::make_unique<Cell>(IVec2{ x, y });
				static_cast<Cell*>(TerrainGrid[CellHead].get())->SetValue(CellValue);
				++CellValue;
				++CellHead;
			}
		}
	}
}

void IWorld::GetCellMap(std::map<IVec2, Cell*>& CellMap)
{
	for (size_t i = m_CellHead; i < (GRID_SIZE_X + 1) * (GRID_SIZE_Y + 1); ++i)
	{
		Cell* CurrentCell = static_cast<Cell*>(TerrainGrid[i].get());
		CellMap.insert({ CurrentCell->Location, CurrentCell });
	}
}

void IWorld::GetWallList(std::vector<Wall*>& WallList)
{
	for (size_t i = m_WallHead; i < m_CellHead; ++i)
	{
		if (!TerrainGrid[i]->IsCell())
		{
			WallList.push_back(static_cast<Wall*>(TerrainGrid[i].get()));
		}
	}
}
