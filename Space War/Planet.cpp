#include "Planet.h"
#include "Vertex.h"
#include "Core.h"


void Planet::UpdateBuffer(D3DXVECTOR2 size)
{
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

Planet::Planet(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 size, Race race)
	:position{ 0.0f, 0.0f }, texture{ nullptr }
{
	device->CreateVertexBuffer(sizeof(Vertex) * 4, D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_DEFAULT, &vb, nullptr);
	D3DXMatrixIdentity(&transform);
	SetRace(race);
	UpdateBuffer(size);
	speedOfRotate = rand() % 1000 * 0.001f;
}


Planet::~Planet()
{
}

void Planet::SetRace(Race race)
{
	this->race = race;
	switch (race)
	{
	case Race::Red:
		texture = Core::FindTexture("red planet");
		break;
	case Race::Green:
		texture = Core::FindTexture("green planet");
		break;
	case Race::Blue:
		texture = Core::FindTexture("blue planet");
		break;
	}
}

void Planet::Draw(LPDIRECT3DDEVICE9 device)
{
	device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	device->SetTexture(0, texture);
	device->SetTransform(D3DTS_WORLD, &transform);
	device->SetStreamSource(0, vb, 0, sizeof(Vertex));
	device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
}

void Planet::Update(float time)
{
	angle += time * speedOfRotate*20;
	D3DXMATRIX rot, tr, sca;
	D3DXMatrixScaling(&sca, 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationZ(&rot, D3DXToRadian(angle));
	D3DXMatrixTranslation(&tr, position.x, position.y,0.0f);
	transform = sca * rot * tr;
}
