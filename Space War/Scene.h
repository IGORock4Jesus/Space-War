#pragma once

#include "ECS.h"

constexpr size_t MAX_ENTITIES = 100000;

class Scene
{
	ECS::Entity* entities[MAX_ENTITIES];

public:
	Scene();
	~Scene();

	ECS::Entity* CreateEntity();
	void AddEntity(ECS::Entity* e);
	void RemoveEntity(ECS::Entity* e);
	void ClearEntities();
	ECS::Entity* FindEntity(std::string name);
};

