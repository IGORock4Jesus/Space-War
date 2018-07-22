#include "Core.h"
#include <map>

namespace Core {

	struct Vertex
	{
		D3DXVECTOR4 pos;
		D3DCOLOR color;
	};

	HINSTANCE hinstance;
	HWND hwnd;
	LPDIRECT3D9 direct3d;
	LPDIRECT3DDEVICE9 device3d;
	LPCSTR windowClass = "GAME WINDOW";
	Desc desc;
	std::map<std::string, LPDIRECT3DTEXTURE9> textures;
	D3DXMATRIX viewTransform, projTransform;

	LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
		switch (m)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
			if (desc.OnKeyDown)
				desc.OnKeyDown(w);
			return 0;
		default:
			return DefWindowProc(h, m, w, l);
		}
	}

	bool InitializeWindow() {
		WNDCLASS wc{ 0 };
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hInstance = hinstance;
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = windowClass;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClass(&wc);
		int screenWidth = GetSystemMetrics(SM_CXSCREEN) / 2;
		int screenHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
		RECT r{ screenWidth - 400, screenHeight - 300, screenWidth + 400,screenHeight + 300 };
		AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
		hwnd = CreateWindow(windowClass, windowClass, WS_OVERLAPPEDWINDOW, r.left, r.top, r.right - r.left, r.bottom - r.top, HWND_DESKTOP, nullptr, hinstance, nullptr);
		if (!hwnd)
			return false;

		ShowWindow(hwnd, SW_NORMAL);

		return true;
	}

	bool InitializeRenderer() {
		if (!(direct3d = Direct3DCreate9(D3D_SDK_VERSION)))
			return false;

		D3DPRESENT_PARAMETERS pp{ 0 };
		pp.BackBufferFormat = D3DFMT_A8R8G8B8;
		pp.BackBufferWidth = 800;
		pp.BackBufferHeight = 600;
		pp.hDeviceWindow = hwnd;
		pp.Windowed = true;
		pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		if (FAILED(direct3d->CreateDevice(0, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &device3d)))
			return false;

		device3d->SetRenderState(D3DRS_LIGHTING, FALSE);
		// Устанавливаем коэффициенты смешивания таким образом,
		// чтобы альфа-компонента определяла прозрачность
		device3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		return true;
	}
	bool Initialize(HINSTANCE hinstance, Desc* desc) {
		if (!hinstance || !desc)
			return false;

		Core::hinstance = hinstance;
		Core::desc = *desc;

		if (!InitializeWindow())
			return false;

		if (!InitializeRenderer())
			return false;

		D3DXMatrixLookAtRH(&viewTransform, &D3DXVECTOR3(0.0f, 0.0f, -10.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, -1.0f, 0.0f));
		D3DXMatrixOrthoOffCenterRH(&projTransform, -400, 400, 300, -300, 0.1f, 100000.0f);

		return true;
	}
	void Release() {
		for (auto& t : textures) {
			t.second->Release();
		}
		textures.clear();
		if (device3d) {
			device3d->Release();
			device3d = nullptr;
		}
		if (direct3d) {
			direct3d->Release();
			direct3d = nullptr;
		}
		hwnd = nullptr;
		hinstance = nullptr;
	}

	void Rendering() {
		device3d->Clear(0, nullptr, D3DCLEAR_TARGET, 0xff404040, 1.0f, 0);
		device3d->BeginScene();

		device3d->SetTransform(D3DTS_VIEW, &viewTransform);
		device3d->SetTransform(D3DTS_PROJECTION, &projTransform);

		if (desc.OnRendering)
			desc.OnRendering(device3d);

		device3d->EndScene();
		device3d->Present(0, 0, 0, 0);
	}

	void Run() {
		MSG msg{ 0 };
		DWORD ot = timeGetTime();
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				DWORD nt = timeGetTime();
				float elapsed = (nt - ot)*0.001f;
				ot = nt;
				if (desc.OnUpdate)
					desc.OnUpdate(elapsed);

				Rendering();
			}
		}
	}
	HINSTANCE GetHInstance() { return hinstance; }
	HWND GetHWND() { return hwnd; }
	LPDIRECT3D9 GetDirect() { return direct3d; }
	LPDIRECT3DDEVICE9 GetDevice() { return device3d; }
	void CloseWindow()
	{
		DestroyWindow(hwnd);
	}

	LPDIRECT3DTEXTURE9 FindTexture(std::string name)
	{
		return textures[name];
	}


	bool LoadTexture(std::string name, std::string path) {
		LPDIRECT3DTEXTURE9 texture;
		if (FAILED(D3DXCreateTextureFromFile(device3d, path.c_str(), &texture)))
			return false;
		textures.insert({ name, texture });
		return true;
	}

	void DrawImage(float x, float y, float w, float h, std::string name, float angle) {
		/*Vertex vs[]{
			{ { x,y,0,1 },			{ 0,0 } },
			{ { x + w,y,0,1 },		{1,0 } },
			{ { x + w,y + h,0,1 },	{ 1,1 } },
			{ {x,y + h,0,1},		{0,1} },
		};
		device3d->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
		device3d->SetTexture(0, textures[name]);
		device3d->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vs, sizeof(Vertex));*/

		/*if (SUCCEEDED(sprite->Begin(D3DXSPRITE_ALPHABLEND))) {
			D3DXVECTOR3 pos{ x,y,0 };
			RECT r{ x,y,x + w,y + h };

			D3DXMATRIX m;
			auto c = D3DXVECTOR2(w / 2, h / 2);
			D3DXMatrixAffineTransformation2D(&m, 1, &c, D3DXToRadian(angle), &D3DXVECTOR2(x, y));
			sprite->SetTransform(&m);

			sprite->Draw(textures[name], 0, 0, 0, 0xffffffff);
			sprite->End();
		}*/
	}
	void DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR color)
	{
		Vertex vs[]{
			{ { x1,y1,0,1 }, color },
			{{x2,y2,0,1}, color},
		};
		device3d->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		device3d->DrawPrimitiveUP(D3DPT_LINELIST, 1, vs, sizeof(Vertex));
	}
}