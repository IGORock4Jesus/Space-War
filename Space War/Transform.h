#pragma once
#include "ECS.h"
#include <d3dx9.h>


class Transform : public ECS::Component
{
	D3DXVECTOR2 position{ 0.0f, 0.0f };
	float angle{ 0.0f };
	D3DXMATRIX transform;

	void Update(){
		D3DXMATRIX tr, rot;
		D3DXMatrixRotationZ(&rot, D3DXToRadian(angle));
		D3DXMatrixTranslation(&tr, position.x, position.y, 0.0f);
		transform = rot * tr;
	}
public:
	Transform()
		: ECS::Component(ECS::GetComponentHash<Transform>())
	{
		D3DXMatrixIdentity(&transform);
	}

	void SetPosition(D3DXVECTOR2 pos) {
		position = pos;
		Update();
	}

	void SetAngle(float a) {
		angle = a;
		Update();
	}

	const D3DXMATRIX GetMatrix() const { return transform; }
};
