#pragma once

#include "GameStack.h"


class LogoGameStackItem : public IGameStackItem
{
public:
	LogoGameStackItem();
	~LogoGameStackItem();

	virtual void Initialize() override;
	virtual void Release() override;
};

