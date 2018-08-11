#include <d3dx9.h>
#include <vector>
#include "Core.h"
#include "Race.h"
#include "Planet.h"
#include "Sprite.h"
#include "PlanetRotation.h"	
#include "Scene.h"
#include "GalaxyManager.h"
#include "Label.h"
#include "LogoGameStackItem.h"




constexpr float SHIP_SIZE = 5.0f;
float r1, r2;
std::vector<Planet*> planets;

TransformSystem transformSystem;
SpriteSystem spriteSystem;
PlanetRotationSystem planetRotationSystem;
LabelSystem labelSystem;

std::vector<ECS::SystemBase*> systems;
Scene scene;
GalaxyManager galaxyManager;
GameStack *gameStack;


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
	/*Core::DrawImage(20, 20, 128, 128, "test", r1);
	Core::DrawImage(200, 20, 128, 128, "test1", r2);

	DrawShip(Race::Blue, 20, 300);
	DrawShip(Race::Red, 120, 300);
	DrawShip(Race::Green, 220, 300);*/

	for (auto p : planets) {
		p->Draw(device);
	}

	for (auto s : systems)
		s->Render(device);
}

bool LoadImages() {
	if (!Core::LoadTexture("red planet", R"(..\textures\planet_a.png)"))
		return false;

	if (!Core::LoadTexture("blue planet", R"(..\textures\planet_b.png)"))
		return false;

	return true;
}

void OnUpdate(float elapsedTime) {
	r1 += 17.f * elapsedTime * 100;
	r2 += 3.f * elapsedTime * 100;

	for (auto p : planets) {
		p->Update(elapsedTime);
	}

	for (auto s : systems)
		s->Update(elapsedTime);
}

void ClearPlanets() {
	for (auto p : planets) {
		delete p;
	}
	planets.clear();
}

ECS::Entity* CreatePlanet(D3DXVECTOR2 position, float rotateSpeed) {
	auto entity = new ECS::Entity();
	Transform* t = transformSystem.Create(entity);
	t->SetPosition(position);

	Sprite* s = spriteSystem.Create(entity, t, Core::GetDevice(), D3DXVECTOR2{ 100, 100 });
	s->SetTexture(Core::FindTexture("red planet"));

	PlanetRotation* rotation = planetRotationSystem.Create(entity, t);
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
	Transform* t = transformSystem.Create(entity);
	t->SetPosition({ 100, y });
	Label* label = labelSystem.Create(entity, Core::GetDevice());
	label->SetText(text);
	label->SetSize({200,50 });
	return entity;
}

void LoadGame() {
	systems = {
		&transformSystem,
		&spriteSystem,
		&planetRotationSystem,
		&labelSystem
	};

	gameStack = new GameStack(&scene);
	gameStack->Push(gameStack->Create<LogoGameStackItem>());

	/*ClearPlanets();

	galaxyManager.Load();

	for (int i = 0; i < galaxyManager.GetGalaxyCount(); i++)
	{
		scene.AddEntity(CreateGalaxyDesc(galaxyManager.GetGalaxyName(i)));
	}*/
}

void ReleaseGame() {
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