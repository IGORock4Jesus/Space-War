#pragma once

#include <stack>
#include <d3d9.h>

class Scene;
class GameStack;

class IGameStackItem
{
	friend GameStack;
	Scene* scene;
	GameStack* gameStack;

protected:
	Scene * GetScene() { return scene; }
	GameStack* GetGameStack() { return gameStack; }


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

	Scene* scene;

public:
	GameStack(Scene* scene);
	~GameStack();

	void Push(IGameStackItem* item);
	void Pop();

	void Render(LPDIRECT3DDEVICE9 device);
	void Update(float time);

	template <typename T, typename... Args>
	T* Create(Args... args) {
		static_assert(std::is_base_of_v<IGameStackItem, T>, "T должен наследовать IGameStackItem.");
		T* t = new T(args...);
		t->scene = scene;
		t->gameStack = this;
		return t;
	}
};

