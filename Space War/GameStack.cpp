#include "GameStack.h"



GameStack::GameStack(Scene* scene)
	: scene{ scene }
{
}


GameStack::~GameStack()
{
	while (stack.size() != 0)
		Pop();
}

void GameStack::Push(IGameStackItem * item)
{
	// если в стеке есть элементы - замораживаем его
	if (!stack.empty()) {
		auto p = stack.top();
		p->Suspend();
	}

	item->Initialize();

	stack.push(item);
}

void GameStack::Pop()
{
	if (!stack.empty()) {
		auto p = stack.top();
		stack.pop();
		p->Release();
		delete p;
	}

	if (!stack.empty()) {
		stack.top()->Resume();
	}
}

void GameStack::Render(LPDIRECT3DDEVICE9 device)
{
}

void GameStack::Update(float time)
{
	if (!stack.empty()) {
		stack.top()->Update(time);
	}
}
