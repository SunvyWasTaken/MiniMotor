
#include "Cell.h"

#include "MazeTerrain.h"

#include "MiniDebug/Debug.h"

namespace
{
	const IVec2 Sides[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	const IVec2 Diagonals[4] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	const TextureCoord WallTextureCoord = { IVec2{0, 0}, IVec2{438, 0}, IVec2{438, 438}, IVec2{0, 438} };
	const TextureCoord PathTextureCoord = { IVec2{438, 0}, IVec2{876, 0}, IVec2{876, 438}, IVec2{438, 0} };
}

void Cell::BeginPlay()
{
	AddComponent<RendableComponent>(Texture{ TEXT("Ressources/Brick_Block.png"), WallTextureCoord });
	std::visit(overloaded(
		[&](Wall tmp)
		{
			GetComponent<RendableComponent>().SetTextureCoord(WallTextureCoord);
		},
		[&](Path tmp)
		{
			GetComponent<RendableComponent>().SetTextureCoord(PathTextureCoord);
		}
	), state);
}

MazeTerrain* Cell::GetWorld()
{
	return static_cast<MazeTerrain*>(Entity::GetWorld());
}

void Cell::ChangeValue(const uint64_t val)
{
	if (value == val)
		return;

	value = val;
	bool HasToChange = true;
	for (const IVec2& side : Sides)
	{
		IVec2 tmpPos = side + m_Position;
		if (tmpPos.x <= 0 || tmpPos.y <= 0 || tmpPos.x >= GetWorld()->MazeSize.x || tmpPos.y >= GetWorld()->MazeSize.y)
		{
			continue;
		}

		std::visit(overloaded(
			[&](Wall tmp)
			{
				if (!CanbeOpen())
					return;

				if (Cell* curr = GetWorld()->GetCellByPos(tmpPos))
				{
					if (curr->IsState<Path>())
					{
						if (curr->value != val)
						{
							HasToChange = false;
							return;
						}
					}
				}
			},
			[&](Path tmp)
			{
				Cell* tmpEnt = GetWorld()->Maze[tmpPos.x * GetWorld()->MazeSize.x + tmpPos.y];
				tmpEnt->ChangeValue(val);
			}
		), state);
	}
	if (IsState<Wall>() && HasToChange)
	{
		GetWorld()->RemoveWall(m_Position);
		std::get<Wall>(state).bCanBeOpen = false;
	}
}

void Cell::ChangeState(const CellState& newState)
{
	state = newState;
	std::visit(overloaded(
		[&](Wall tmp)
		{
			GetComponent<RendableComponent>().SetTextureCoord(WallTextureCoord);
		},
		[&](Path tmp)
		{
			GetComponent<RendableComponent>().SetTextureCoord(PathTextureCoord);
		}
	), state);
}

bool Cell::CanbeOpen() const
{
	return std::visit(overloaded(
		[&](Wall tmp)
		{
			return tmp.bCanBeOpen;
		},
		[&](Path tmp)
		{
			return false;
		})
		, state);
}

void Cell::SetCanBeOpen(const bool bOpen)
{
	if (IsState<Wall>())
	{
		std::get<Wall>(state).bCanBeOpen = bOpen;
	}
}

const NeighboursList& Cell::GetNeighbours()
{
	NeighboursList Neighbours;

	for (size_t i = 0; i < 4; ++i)
	{
		IVec2 pos = m_Position + Sides[i];
		if (pos.x < 0 || pos.y < 0 || pos.x >= GetWorld()->MazeSize.x || pos.y >= GetWorld()->MazeSize.y)
		{
			Neighbours[i] = nullptr;
			continue;
		}

		Neighbours[i] = GetWorld()->GetCellByPos(pos);
	}

	return Neighbours;
}

uint64_t Cell::GetFirstValideValue()
{
	for (auto curr : GetNeighbours())
	{
		if (curr && curr->IsState<Path>())
		{
			return curr->value;
		}
	}
	return value;
}
