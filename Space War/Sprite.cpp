#include "Sprite.h"
#include "Vertex.h"


Sprite::Sprite(LPDIRECT3DDEVICE9 device,D3DXVECTOR2 size)
	: ECS::Component(ECS::GetComponentHash<Sprite>())
{
	device->CreateVertexBuffer(sizeof(Vertex) * 4, D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_DEFAULT, &vb, nullptr);
	D3DXMatrixIdentity(&transform);
	SetRace(race);

	Vertex vs[]{
		{ { -size.x / 2, -size.y / 2, 0.0f },{ 0.0f, 0.0f } },
		{ { -size.x / 2, size.y / 2, 0.0f },{ 1.0f, 0.0f } },
		{ { size.x / 2, size.y / 2, 0.0f },{ 1.0f, 1.0f } },
		{{size.x / 2, -size.y / 2, 0.0f}, {0.0f, 1.0f}},
	};
	LPVOID data;
	if (SUCCEEDED(vb->Lock(0, 0, &data, 0))) {
		memcpy(data, vs, sizeof(Vertex) * 4);
		vb->Unlock();
	}
}


Sprite::~Sprite()
{
	if (vb)vb->Release();
}

void SpriteSystem::Render()
{
}
