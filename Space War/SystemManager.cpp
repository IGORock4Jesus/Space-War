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

void SystemManager::Render(LPDIRECT3DDEVICE9 device)
{
	for (size_t i = 0; i < count; i++)
	{
		systems[i]->Render(device);
	}
}

void SystemManager::Update(float time)
{
	for (size_t i = 0; i < count; i++)
	{
		systems[i]->Update(time);
	}
}
