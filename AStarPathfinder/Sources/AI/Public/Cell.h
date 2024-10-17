
#pragma once

#include "CoreMinimal.h"
#include "ECS/Entitys.h"
#include "MazeTerrain.h"

class Wall
{
public:

	Wall() = default;

	bool bCanBeOpen = false;
};

class Path
{
public:

	Path() = default;
};

using CellState = std::variant<Wall, Path>;
using NeighboursList = std::array<class Cell*, 4>;

class Cell final : public Entity
{
public:

	template <typename CellType>
	Cell(const uint64_t val, const CellType& cellstateType, const IVec2& pos)
		: Entity()
		, value(val)
		, state(cellstateType)
		, m_Position(pos)
		, beforePath(nullptr)
		, gCost(0)
		, hCost(0)
	{
		static_assert(IsTypeInList<CellType, CellState>::value, "Type given is a celltype");
	}

	void BeginPlay() override;

	MazeTerrain* GetWorld();

	void ChangeValue(const uint64_t val);

	void ChangeState(const CellState& newState);

	bool CanbeOpen() const;

	void SetCanBeOpen(const bool bOpen);

	template <typename CellType>
	bool IsState() const
	{
		return std::holds_alternative<CellType>(state);
	}

	const NeighboursList& GetNeighbours();

	uint64_t GetFirstValideValue();

	uint64_t value;

	CellState state;

	// Position in the Mazelist by (currX * MazeSize.x + currY)
	IVec2 m_Position;

	// A* Pathfinding
	Cell* beforePath;

	uint64_t gCost;

	uint64_t hCost;

};
