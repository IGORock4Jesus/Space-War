#pragma once
#include <d3dx9.h>
#include <string>
#include <vector>

namespace Core {
	struct Desc
	{
		void(*OnRendering)(LPDIRECT3DDEVICE9 device);
		void(*OnKeyDown)(int key);
		void(*OnUpdate)(float elapsedTime);
	};

	bool Initialize(HINSTANCE hinstance, Desc* desc);
	void Release();
	void Run();
	HINSTANCE GetHInstance();
	HWND GetHWND();
	LPDIRECT3D9 GetDirect();
	LPDIRECT3DDEVICE9 GetDevice();
	void CloseWindow();
	LPDIRECT3DTEXTURE9 FindTexture(std::string name);

	bool LoadTexture(std::string name, std::string path);
	void DrawImage(float x, float y, float w, float h, std::string name, float angle = 0.0f);
	void DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR color);

	std::vector<char> LoadFile(std::string filename, std::string* error = nullptr);

	void Log(std::string text);
}