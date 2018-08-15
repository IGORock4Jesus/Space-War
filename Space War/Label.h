#pragma once

#include "ECS.h"
#include "Transform.h"

class Label : public ECS::Component<Label>
{
	Transform* transform{ nullptr };
	std::string text;
	D3DXVECTOR2 size{ 0,0 };

	LPD3DXFONT font{ nullptr };
	
	friend class LabelSystem;

	void Render(LPDIRECT3DDEVICE9 device);
public:
	Label(LPDIRECT3DDEVICE9 device);
	~Label();

	virtual void OnInitialize(ECS::Entity* entity) override;

	void SetText(std::string text) { this->text = text; }
	void SetSize(D3DXVECTOR2 size) { this->size = size; }
};


class LabelSystem : public ECS::System<LabelSystem, Label> {
public:
	virtual void OnComponentRender(Label* label, LPDIRECT3DDEVICE9 device) override;
};
