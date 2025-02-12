#pragma once

class Entity;

class Scene
{
public:
	Scene();
	virtual ~Scene();



	std::vector<Entity> entitys;
};
