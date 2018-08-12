#include "SystemManager.h"



SystemManager::SystemManager(ECS::SystemBase** systems, int count)
	: systems{ systems }, count{ count }
{
}


SystemManager::~SystemManager()
{
	for (size_t i = 0; i < count; i++)
	{
		delete systems[i];
	}
	delete[] systems;
}
