#pragma once

#include "ECS.h"
#include <d3dx9.h>

class Sprite : ECS::Component
{
	LPDIRECT3DTEXTURE9 texture{ nullptr };
	LPDIRECT3DVERTEXBUFFER9 vb{ nullptr };

public:
	Sprite(D3DXVECTOR2 size);
	~Sprite();
};

class SpriteSystem : ECS::System<Sprite> 
{
public:
	virtual void Render() override;
};

