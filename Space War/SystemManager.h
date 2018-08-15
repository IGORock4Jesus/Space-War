#pragma once

#include "ECS.h"
#include <d3d9.h>

class SystemManager
{
	ECS::SystemBase** systems;
	const int count;

public:
	SystemManager(ECS::SystemBase** systems, int count);
	~SystemManager();

	// T - должен быть компонентом.
	template <typename T>
	ECS::System<T>* Get() {
		static_assert(std::is_base_of_v<ECS::ComponentBase, T>, "T должен наследовать ECS::ComponentBase.");
		for (size_t i = 0; i < count; i++)
		{
			if (ECS::GetComponentHash<ECS::System<T>>() == systems[i]->hashType)
				return (ECS::System<T>*)systems[i];
		}
		throw std::exception("”казанна€ система компонентов - не существует.");
	}

	void Render(LPDIRECT3DDEVICE9 device);
	void Update(float time);
};

