#pragma once

#include "GameStack.h"
#include <vector>
#include "PLanetDesc.h"


class PlayGameStackItem : public IGameStackItem
{
public:
	PlayGameStackItem(const std::vector<PlanetDesc>& planets);
	~PlayGameStackItem();
};

