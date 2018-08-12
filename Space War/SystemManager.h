#pragma once

#include "ECS.h"


class SystemManager
{
	ECS::SystemBase** systems;
	const int count;

public:
	SystemManager(ECS::SystemBase** systems, int count);
	~SystemManager();

	template <typename T>
	T* Get() {
		static_assert(std::is_base_of_v<ECS::SystemBase, T>, "T должен наследовать ECS::SystemBase.");
		for (size_t i = 0; i < count; i++)
		{
			if(ECS::GetComponentHash<)
		}
	}
};

