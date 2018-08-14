#pragma once

#include "GameStack.h"
#include "GalaxyManager.h"


class LogoGameStackItem : public IGameStackItem
{
	GalaxyManager galaxyManager;

	void CreateGalaxyButton(float y, std::string textureName);
public:
	LogoGameStackItem();
	~LogoGameStackItem();

	virtual void Initialize() override;
	virtual void Release() override;
};

