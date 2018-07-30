#pragma once
#include "ECS.h"
#include <d3dx9.h>


class Transform : public ECS::Component<Transform>
{
	D3DXVECTOR2 position{ 0.0f, 0.0f };
	float angle{ 0.0f };
	D3DXMATRIX transform;

	void Update() {
		D3DXMATRIX tr, rot;
		D3DXMatrixRotationZ(&rot, D3DXToRadian(angle));
		D3DXMatrixTranslation(&tr, position.x, position.y, 0.0f);
		transform = rot * tr;
	}
public:
	Transform()
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

	const float GetAngle()const { return angle; }

	const D3DXMATRIX GetMatrix() const { return transform; }
};


class TransformSystem : public ECS::System<Transform> {

public:

};