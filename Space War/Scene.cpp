#include "Scene.h"



Scene::Scene()
{
	ZeroMemory(entities, sizeof(ECS::Entity*) * MAX_ENTITIES);
}


Scene::~Scene()
{
	ClearEntities();
}

ECS::Entity * Scene::CreateEntity()
{
	for (size_t i = 0; i < MAX_ENTITIES; i++)
	{
		if (!entities[i]) {
			auto e = new ECS::Entity();
			entities[i] = e;
			return e;
		}
	}
	return nullptr;
}

void Scene::AddEntity(ECS::Entity * e)
{
	for (size_t i = 0; i < MAX_ENTITIES; i++)
	{
		if (!entities[i]) {
			entities[i] = e;
			return;
		}
	}
}

void Scene::RemoveEntity(ECS::Entity * e)
{
	for (size_t i = 0; i < MAX_ENTITIES; i++)
	{
		if (entities[i] == e) {
			entities[i] = nullptr;
			delete e;
			return;
		}
	}
}

void Scene::ClearEntities()
{
	for (size_t i = 0; i < MAX_ENTITIES; i++)
	{
		if (entities[i]) {
			delete entities[i];
			entities[i] = nullptr;
		}
	}
}

ECS::Entity * Scene::FindEntity(std::string name)
{
	for (size_t i = 0; i < MAX_ENTITIES; i++)
	{
		if (entities[i] && entities[i]->GetName() == name) {
			return entities[i];
		}
	}
	return nullptr;
}
