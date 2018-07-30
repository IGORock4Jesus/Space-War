#pragma once

#include "ECS.h"
#include <d3dx9.h>
#include "Transform.h"


class Sprite : public ECS::Component
{
	LPDIRECT3DTEXTURE9 texture{ nullptr };
	LPDIRECT3DVERTEXBUFFER9 vb{ nullptr };
	Transform* transform{ nullptr };

public:
	Sprite(Transform* transform, LPDIRECT3DDEVICE9 device, D3DXVECTOR2 size);
	~Sprite();

	void Draw(LPDIRECT3DDEVICE9 device);

	void SetTexture(LPDIRECT3DTEXTURE9 tex) { texture = tex; }
};

class SpriteSystem : public ECS::System<Sprite>
{
public:
	virtual void Render(LPDIRECT3DDEVICE9 device) override;
};

