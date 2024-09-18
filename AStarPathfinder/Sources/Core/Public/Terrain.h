#pragma once

#include "Entitys.h"
#include "Setting.h"

#include <array>
#include <map>
#include <memory>

class Cell;
class IEntity;

template <typename RendeType>
class IDraw;


using Entitys = std::vector<std::unique_ptr<IEntity>>;

class IWorld
{
public:

	IWorld();

	Cell* SetCellAt(size_t Index);

	template <typename type>
	type* SpawnEntity(IVec2 Location)
	{
		EntityList.push_back(std::make_unique<type>(Location));
		return (type*)EntityList[EntityList.size() - 1].get();
	}

	void FillWorldGrid();

	template <typename RendeType>
	void BufferFrameEntitys(IDraw<RendeType>& targetDraw)
	{
		// Draw the terrain.
		for (size_t i = 0; i < TerrainGrid.size(); ++i)
		{
			targetDraw.BufferFrame(TerrainGrid[i].get());
		}
		// Next the Entity
		for (int nbr = 0; nbr < EntityList.size(); ++nbr)
		{
			targetDraw.BufferFrame(EntityList[nbr].get());
		}
	}

	void GetCellMap(std::map<IVec2, Cell*>& CellMap);

	void GetWallList(std::vector<Wall*>& WallList);

	Entitys EntityList;
	std::array<std::unique_ptr<IEntity>, (GRID_SIZE_X + 1)* (GRID_SIZE_Y + 1)> TerrainGrid;
	size_t m_BorderHead;
	size_t m_WallHead;
	size_t m_CellHead;

	int previousFrameLoad = 0;
	int currentFrameLoad = 0;
};