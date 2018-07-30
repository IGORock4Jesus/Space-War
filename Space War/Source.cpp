#include <d3dx9.h>
#include <vector>
#include "Core.h"
#include "Race.h"
#include "Planet.h"


constexpr float SHIP_SIZE = 5.0f;
float r1, r2;
std::vector<Planet*> planets;

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
}

bool LoadImages() {
	if (!Core::LoadTexture("red planet", R"(..\textures\planet_a.png)"))
		return false;

	if (!Core::LoadTexture("blue planet", R"(..\textures\planet_b.png)"))
		return false;

	return true;
}

void OnUpdate(float elapsedTime) {
	r1 += 17.f * elapsedTime*100;
	r2 += 3.f * elapsedTime*100;

	for (auto p : planets) {
		p->Update(elapsedTime);
	}
}

void ClearPlanets() {
	for (auto p : planets) {
		delete p;
	}
	planets.clear();
}
void LoadGame() {
	ClearPlanets();
	auto p = new Planet(Core::GetDevice(), { 100,100 }, Race::Red);
	p->SetPosition({ -200, 0 });
	planets.push_back(p);
	planets.push_back(new Planet(Core::GetDevice(), { 70,70 }, Race::Blue));
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