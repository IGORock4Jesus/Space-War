#pragma once

#include "ECS.h"
#include <d3dx9.h>
#include "Transform.h"


class Sprite : public ECS::Component<Sprite>
{
	LPDIRECT3DTEXTURE9 texture{ nullptr };
	LPDIRECT3DVERTEXBUFFER9 vb{ nullptr };
	Transform* transform{ nullptr };

public:
	Sprite(Transform* transform, LPDIRECT3DDEVICE9 device, D3DXVECTOR2 size);
	~Sprite();

	void Draw(LPDIRECT3DDEVICE9 device);
	void SetTexture(LPDIRECT3DTEXTURE9 t) { texture = t; }
};

class SpriteSystem : public ECS::System<Sprite>
{
private:
	virtual void OnComponentRender(Sprite* component, LPDIRECT3DDEVICE9 device) override;
};

