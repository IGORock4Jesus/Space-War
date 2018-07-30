#include <d3dx9.h>
#include <vector>
#include "Core.h"
#include "Race.h"
#include "Planet.h"
#include "Sprite.h"
#include "PlanetRotation.h"	


constexpr float SHIP_SIZE = 5.0f;
float r1, r2;
std::vector<Planet*> planets;

TransformSystem transformSystem;
SpriteSystem spriteSystem;
PlanetRotationSystem planetRotationSystem;
std::vector<ECS::SystemBase*> systems;

ECS::Entity* entity;


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
void LoadGame() {
	systems = {
		&transformSystem,
		&spriteSystem,
		&planetRotationSystem
	};


	ClearPlanets();
	auto p = new Planet(Core::GetDevice(), { 100, 100 }, Race::Red);
	p->SetPosition({ -200, 0 });
	planets.push_back(p);
	planets.push_back(new Planet(Core::GetDevice(), { 70, 70 }, Race::Blue));

	Transform* t = new Transform();
	t->SetPosition({ 20,20 });
	transformSystem.Add(t);

	Sprite* s = new Sprite(t, Core::GetDevice(), { 100, 100 });
	s->SetTexture(Core::FindTexture("red planet"));
	spriteSystem.Add(s);

	PlanetRotation* rotation = new PlanetRotation(t);
	rotation->SetSpeed(-100.0f);
	planetRotationSystem.Add(rotation);

	entity = new ECS::Entity();
	entity->AddComponent(t);
	entity->AddComponent(s);
	entity->AddComponent(rotation);

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