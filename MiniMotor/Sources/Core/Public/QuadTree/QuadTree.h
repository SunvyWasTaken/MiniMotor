// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"

template <typename DataType, typename MetricType>
class T2DQuadTree final
{
	using TreeType = T2DQuadTree<DataType, MetricType>;
	using TreePtr = std::unique_ptr<TreeType>;

public:
	
	T2DQuadTree()
		: m_Size(0)
		, m_Position(0)
		, m_CurrentDataIndex(0)
	{
	}

	explicit T2DQuadTree(const MetricType& position, const MetricType& size)
		: m_Size(size)
		, m_Position(position)
		, m_CurrentDataIndex(0)
	{
	}

	~T2DQuadTree() = default;

	void AddData(DataType data, const FTrans2& pos)
	{
		if (m_CurrentDataIndex >= 4)
		{
			if (m_Children[0] == nullptr)
			{
				MetricType halfSize = m_Size / 2;
				m_Children[0] = std::make_unique<TreeType>(m_Position, halfSize);
				m_Children[1] = std::make_unique<TreeType>(MetricType{ m_Position.x, m_Position.y + halfSize.y }, halfSize);
				m_Children[2] = std::make_unique<TreeType>(MetricType{ m_Position.x + halfSize.x, m_Position.y }, halfSize);
				m_Children[3] = std::make_unique<TreeType>(MetricType{ m_Position.x + halfSize.x, m_Position.y + halfSize.y }, halfSize);

				for (auto& [key, val] : m_Data)
				{
					PropagateData(key, val);
				}
				m_Data.clear();
			}

			PropagateData(data, pos);
			return;
		}
		else
		{
			m_Data.emplace(data, pos);
			++m_CurrentDataIndex;
			return;
		}
	}

	void GetData(std::vector<DataType>& data, const FTrans2& targetPos)
	{
		if (m_CurrentDataIndex >= 4)
		{
			for (int i = 0; i < m_Children.size(); ++i)
			{
				if (m_Children[i] == nullptr)
				{
					for (auto& [key, val] : m_Data)
					{
						data.push_back(key);
					}
					return;
				}
				if (((m_Children[i]->m_Position.x <= targetPos.pos.x && m_Children[i]->m_Position.x + m_Children[i]->m_Size.x >= targetPos.pos.x)
					|| (m_Children[i]->m_Position.x <= targetPos.pos.x + targetPos.scale.x && m_Children[i]->m_Position.x + m_Children[i]->m_Size.x >= targetPos.pos.x + targetPos.scale.x))
					&& ((m_Children[i]->m_Position.y <= targetPos.pos.y && m_Children[i]->m_Position.y + m_Children[i]->m_Size.y >= targetPos.pos.y)
					|| (m_Children[i]->m_Position.y <= targetPos.pos.y + targetPos.scale.y && m_Children[i]->m_Position.y + m_Children[i]->m_Size.y >= targetPos.pos.y + targetPos.scale.y)))
				{
					m_Children[i]->GetData(data, targetPos);
				}
			}
		}
		else
		{
			for (auto& [key, val] : m_Data)
			{
				data.push_back(key);
			}
		}
	}

	void PropagateData(DataType data, const FTrans2& pos)
	{
		for (size_t i = 0; i < m_Children.size(); ++i)
		{
			if (((m_Children[i]->m_Position.x <= pos.pos.x && m_Children[i]->m_Position.x + m_Children[i]->m_Size.x >= pos.pos.x)
				|| (m_Children[i]->m_Position.x <= pos.pos.x + pos.scale.x && m_Children[i]->m_Position.x + m_Children[i]->m_Size.x >= pos.pos.x + pos.scale.x))
				&& ((m_Children[i]->m_Position.y <= pos.pos.y && m_Children[i]->m_Position.y + m_Children[i]->m_Size.y >= pos.pos.y)
				|| (m_Children[i]->m_Position.y <= pos.pos.y + pos.scale.y && m_Children[i]->m_Position.y + m_Children[i]->m_Size.y >= pos.pos.y + pos.scale.y)))
			{
				m_Children[i]->AddData(data, pos);
			}
		}
		return;
	}
		

	// List des données du quadTree.
	std::map<DataType, FTrans2> m_Data;
	
	// Liste des quadTree enfants à celui ci.
	std::array<TreePtr, 4> m_Children;

	MetricType m_Size;

	MetricType m_Position;

	unsigned int m_CurrentDataIndex;

	friend class World;
};
