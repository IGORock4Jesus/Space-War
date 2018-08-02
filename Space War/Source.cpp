#include <d3dx9.h>
#include <vector>
#include "Core.h"
#include "Race.h"
#include "Planet.h"
#include "Sprite.h"
#include "PlanetRotation.h"	
#include "Scene.h"

constexpr float SHIP_SIZE = 5.0f;
float r1, r2;
std::vector<Planet*> planets;

TransformSystem transformSystem;
SpriteSystem spriteSystem;
PlanetRotationSystem planetRotationSystem;
std::vector<ECS::SystemBase*> systems;
Scene scene;


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

	spriteSystem.Render(device);
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
	Transform* t = transformSystem.Create();
	t->SetPosition(position);

	Sprite* s = spriteSystem.Create(t, Core::GetDevice(), D3DXVECTOR2{ 100, 100 });
	s->SetTexture(Core::FindTexture("red planet"));

	PlanetRotation* rotation = planetRotationSystem.Create(t);
	rotation->SetSpeed(rotateSpeed);

	auto entity = new ECS::Entity();
	entity->AddComponent(t);
	entity->AddComponent(s);
	entity->AddComponent(rotation);

	return entity;
}

float frand(float min, float max) {
	float f = rand() / (float)RAND_MAX;
	auto range = max - min;
	f *= range;
	return f + min;
}

void LoadGame() {
	systems = {
		&transformSystem,
		&spriteSystem,
		&planetRotationSystem
	};


	ClearPlanets();

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
		}
	}
	Core::Release();

	return 0;
}