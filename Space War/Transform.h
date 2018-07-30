#pragma once
#include "ECS.h"
#include <d3dx9.h>


class Transform : public ECS::Component
{
	D3DXVECTOR2 position;
	float angle{ 0.0f };
};
