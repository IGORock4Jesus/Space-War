#include <d3dx9.h>
#include <vector>
#include <Windows.h>
#include "Core.h"
#include "Race.h"
#include "Planet.h"
#include "Sprite.h"
#include "PlanetRotation.h"	
#include "Scene.h"
#include "GalaxyManager.h"
#include "Label.h"
#include "LogoGameStackItem.h"
#include "SystemManager.h"



constexpr float SHIP_SIZE = 5.0f;

Scene scene;
GameStack *gameStack;
SystemManager *systemManager;


void OnKeyDown(int key) {
	if (key == VK_ESCAPE)
		Core::CloseWindow();
}

void DrawShip(Race race, float x, float y) {
	auto hs = SHIP_SIZE / 2.0f;
	D3DCOLOR color;
	switch (race)
	{
	case Race::Red:		color = 0xffff0000; break;
	case Race::Green:	color = 0xff00ff00; break;
	case Race::Blue:	color = 0xff0000ff; break;
	}
	Core::DrawLine(x - hs, y - hs, x + hs, y + hs, color);
	Core::DrawLine(x - hs, y + hs, x + hs, y - hs, color);
}

void OnRendering(LPDIRECT3DDEVICE9 device) {
	systemManager->Render(device);
}

bool LoadImages() {
	if (!Core::LoadTexture("red planet", R"(..\textures\planet_a.png)"))
		return false;

	if (!Core::LoadTexture("blue planet", R"(..\textures\planet_b.png)"))
		return false;

	return true;
}

void OnUpdate(float elapsedTime) {
	systemManager->Update(elapsedTime);
}

ECS::Entity* CreatePlanet(D3DXVECTOR2 position, float rotateSpeed) {
	auto entity = new ECS::Entity();
	Transform* t = systemManager->Get<TransformSystem>()->Create(entity);
	t->SetPosition(position);

	Sprite* s = systemManager->Get<SpriteSystem>()->Create(entity, t, Core::GetDevice(), D3DXVECTOR2{ 100, 100 });
	s->SetTexture(Core::FindTexture("red planet"));

	PlanetRotation* rotation = systemManager->Get<PlanetRotationSystem>()->Create(entity, t);
	rotation->SetSpeed(rotateSpeed);

	return entity;
}

float frand(float min, float max) {
	float f = rand() / (float)RAND_MAX;
	auto range = max - min;
	f *= range;
	return f + min;
}

ECS::Entity* CreateGalaxyDesc(std::string text) {
	static float y = 0;
	y += 100;

	ECS::Entity* entity = new ECS::Entity;
	Transform* t = systemManager->Get<TransformSystem>()->Create(entity);
	t->SetPosition({ 100, y });
	Label* label = systemManager->Get<LabelSystem>()->Create(entity, Core::GetDevice());
	label->SetText(text);
	label->SetSize({200,50 });
	return entity;
}

void LoadGame() {
	ECS::SystemBase** systems = new ECS::SystemBase*[4]{
		new TransformSystem(),
		new SpriteSystem(),
		new PlanetRotationSystem(),
		new LabelSystem()
	};
	systemManager = new SystemManager(systems, 4);

	gameStack = new GameStack(&scene, systemManager);
	gameStack->Push(gameStack->Create<LogoGameStackItem>());

}

void ReleaseGame() {
	if (systemManager)
		delete systemManager;
	if (gameStack)
		delete gameStack;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {
	Core::Desc desc{ 0 };
	desc.OnKeyDown = OnKeyDown;
	desc.OnRendering = OnRendering;
	desc.OnUpdate = OnUpdate;

	srand(timeGetTime());

	if (Core::Initialize(hinstance, &desc)) {
		if (LoadImages()) {
			LoadGame();
			Core::Run();
			ReleaseGame();
		}
	}
	Core::Release();

	return 0;
}