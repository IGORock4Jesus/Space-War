#pragma once

#include <d3dx9.h>
#include "Race.h"


class Planet
{
	D3DXVECTOR2 position;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DVERTEXBUFFER9 vb;
	float angle{ 0.0f }, speedOfRotate;
	D3DXMATRIX transform;
	Race race;


	void UpdateBuffer(D3DXVECTOR2 size);

public:
	Planet(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 size, Race race);
	~Planet();

	void SetPosition(D3DXVECTOR2 v) { position = v; }
	void SetTexture(LPDIRECT3DTEXTURE9 t) { texture = t; }
	void SetRace(Race r);

	void Draw(LPDIRECT3DDEVICE9 device);
	void Update(float time);
};

