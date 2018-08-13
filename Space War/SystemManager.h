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

	template <typename T>
	T* Get() {
		static_assert(std::is_base_of_v<ECS::SystemBase, T>, "T ������ ����������� ECS::SystemBase.");
		for (size_t i = 0; i < count; i++)
		{
			if (ECS::GetComponentHash<T>() == systems[i]->hashType)
				return (T*)systems[i];
		}
		throw std::exception("��������� ������� ����������� - �� ����������.");
	}

	void Render(LPDIRECT3DDEVICE9 device);
	void Update(float time);
};

