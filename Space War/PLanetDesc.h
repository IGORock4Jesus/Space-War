#pragma once

#include <d3dx9.h>
#include <string>
#include "Race.h"


struct PlanetDesc
{
	D3DXVECTOR2 position;
	std::string name;
	Race race;
};