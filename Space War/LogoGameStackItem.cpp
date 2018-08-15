#include "LogoGameStackItem.h"
#include "Core.h"
#include "Scene.h"
#include "SystemManager.h"
#include "Transform.h"
#include "Sprite.h"
#include "Label.h"


void LogoGameStackItem::CreateGalaxyButton(float y, std::string name, std::string textureName)
{
	auto entity = GetScene()->CreateEntity();
	auto t = GetSystemManager()->Get<Transform>()->Create(entity);
	t->SetPosition({ 0, y });
	auto sprite = GetSystemManager()->Get<Sprite>()->Create(entity, t, Core::GetDevice(), D3DXVECTOR2{ 100,100 });
	sprite->SetTexture(Core::FindTexture(textureName));
	auto label = GetSystemManager()->Get<Label>()->Create(entity, Core::GetDevice());
	label->SetText(name);
}

LogoGameStackItem::LogoGameStackItem()
{
	Core::Log("LogoGameStackItem::LogoGameStackItem()");
}


LogoGameStackItem::~LogoGameStackItem()
{
	Core::Log("LogoGameStackItem::~LogoGameStackItem()");
}

void LogoGameStackItem::Initialize()
{
	Core::Log("LogoGameStackItem::Initialize()");

	galaxyManager.Load();

	auto title = GetScene()->CreateEntity();


	// создаем представления для всех галактик и размещаем их как спикок
	float y = 50.0f;
	for (size_t i = 0; i < galaxyManager.GetGalaxyCount(); i++)
	{
		// загружаю текстурку
		auto name = galaxyManager.GetGalaxyName(i);
		auto textureName = "galaxyView_" + name;
		Core::LoadTexture(textureName, galaxyManager.GetGalaxyTexturePath(i));

		CreateGalaxyButton(y, name, textureName);

		y += 200;
	}

}

void LogoGameStackItem::Release()
{
	Core::Log("LogoGameStackItem::Release()");
}
