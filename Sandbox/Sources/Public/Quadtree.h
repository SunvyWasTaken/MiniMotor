#pragma once

#include "Collision.h"

#include <glm/glm.hpp>

template <typename T>
class Quadtree
{
	std::array<glm::vec3, 4> loc ={glm::vec3{ -1.f, 1.f, 1.f }, {-1.f, -1.f, 1.f}, {1.f, -1.f, 1.f}, {1.f, 1.f, 1.f}};
	using ItemList = std::vector<T>;

public:
	Quadtree(const glm::vec3& location = glm::vec3(0), const glm::vec3 half_size = glm::vec3(0))
		: Location(location)
		, halfSize(half_size)
	{
		Child.reserve(4);
		data.reserve(4);
	}

	void Push(const T item)
	{
		Rect self;
		self.Location = Location;
		self.Height = halfSize.y;
		self.Width = halfSize.x;

		if (TestCollision(self, item))
		{
			if (data.size() == 4)
			{
				Split();
				return;
			}
			data.emplace_back(item);
		}
		return;
	}

	void Split()
	{
		auto newHalfSize = halfSize/2.f;
		for (int i = 0; i < 4; ++i)
		{
			auto newLoc = Location + loc[i] * halfSize;
			Child.push_back({Location, newHalfSize});
			for (size_t j = 0; j < data.size(); ++j)
			{
				Child.back().Push(data[j]);
				data.erase(data.begin() + j);
			}
		}
	}

	void Get(T rect, ItemList& list)
	{
		Rect self;
		self.Location = Location;
		self.Height = halfSize.y;
		self.Width = halfSize.x;

		if (TestCollision(rect, self))
		{
			for (auto tmp : Child)
			{
				tmp.Get(rect, list);
			}
			for (auto& item : data)
			{
				if (TestCollision(rect, item))
					list.emplace_back(item);
			}
		}
	}

private:
	glm::vec3 Location;
	glm::vec3 halfSize;

	std::vector<Quadtree> Child;
	std::vector<T> data;
};
