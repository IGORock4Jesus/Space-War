#pragma once

#include <stack>
#include <d3d9.h>


class IGameStackItem
{
public:
	virtual void Initialize() {}
	virtual void Release() {}

	virtual void Suspend() {}
	virtual void Resume() {}

	virtual void Update(float time) {}
};

class GameStack
{
	std::stack<IGameStackItem*> stack;

public:
	GameStack();
	~GameStack();

	void Push(IGameStackItem* item);
	void Pop();

	void Render(LPDIRECT3DDEVICE9 device);
	void Update(float time);
};

