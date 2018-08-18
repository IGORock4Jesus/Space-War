#include "Label.h"



void Label::Render(LPDIRECT3DDEVICE9 device)
{
	float x = transform->GetPosition().x, y = transform->GetPosition().y;
	RECT r{ x, y, x + size.x, y + size.y };
	font->DrawTextA(nullptr, text.c_str(), text.length(), &r, DT_CENTER | DT_VCENTER, 0xffffffff);
}

Label::Label(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateFont(device, 25, 0, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, "Consolas", &font);
}


Label::~Label()
{
	if (font) font->Release();
}

void Label::OnInitialize(ECS::Entity * entity)
{
	transform = entity->GetComponent<Transform>();
}

void LabelSystem::OnComponentRender(Label * label, LPDIRECT3DDEVICE9 device)
{
	label->Render(device);
}
