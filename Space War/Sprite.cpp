#include "Sprite.h"
#include "Vertex.h"


Sprite::Sprite(Transform* transform, LPDIRECT3DDEVICE9 device, D3DXVECTOR2 size)
	: transform{ transform }
{
	device->CreateVertexBuffer(sizeof(Vertex) * 4, D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_DEFAULT, &vb, nullptr);

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

void Sprite::Draw(LPDIRECT3DDEVICE9 device)
{
	device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	device->SetTexture(0, texture);
	device->SetTransform(D3DTS_WORLD, &transform->GetMatrix());
	device->SetStreamSource(0, vb, 0, sizeof(Vertex));
	device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
}

void SpriteSystem::OnComponentRender(Sprite* component, LPDIRECT3DDEVICE9 device)
{
	component->Draw(device);
}
