#include <d3dx9.h>
#include "Core.h"

enum class Race {
	Red, Green, Blue,
};

constexpr float SHIP_SIZE = 5.0f;
float r1, r2;

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

void OnRendering() {
	Core::DrawImage(20, 20, 128, 128, "test", r1);
	Core::DrawImage(200, 20, 128, 128, "test1", r2);

	DrawShip(Race::Blue, 20, 300);
	DrawShip(Race::Red, 120, 300);
	DrawShip(Race::Green, 220, 300);
}

bool LoadImages() {
	if (!Core::LoadTexture("test", R"(C:\Users\igoro\source\repos\Space War\textures\planet_a.png)"))
		return false;

	if (!Core::LoadTexture("test1", R"(C:\Users\igoro\source\repos\Space War\textures\planet_b.png)"))
		return false;

	return true;
}

void OnUpdate(float elapsedTime) {
	r1 += 17.f * elapsedTime*100;
	r2 += 3.f * elapsedTime*100;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {
	Core::Desc desc{ 0 };
	desc.OnKeyDown = OnKeyDown;
	desc.OnRendering = OnRendering;
	desc.OnUpdate = OnUpdate;

	if (Core::Initialize(hinstance, &desc)) {
		if (LoadImages()) {
			Core::Run();
		}
	}
	Core::Release();

	return 0;
}