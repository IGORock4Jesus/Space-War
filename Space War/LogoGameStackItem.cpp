#include "LogoGameStackItem.h"
#include "Core.h"
#include "Scene.h"
#include "SystemManager.h"
#include "Transform.h"
#include "Sprite.h"



void LogoGameStackItem::CreateGalaxyButton(float y, std::string textureName)
{
	auto entity = GetScene()->CreateEntity();
	auto t = GetSystemManager()->Get<TransformSystem>()->Create(entity);
	t->SetPosition({ 50, y });
	auto sprite = GetSystemManager()->Get<SpriteSystem>()->Create(entity, t, Core::GetDevice(), D3DXVECTOR2{ 100,100 });
	sprite->SetTexture(Core::FindTexture(textureName));
	
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
		auto name = "galaxyView_" + galaxyManager.GetGalaxyName(i);
		Core::LoadTexture(name, galaxyManager.GetGalaxyTexturePath(i));

		CreateGalaxyButton(y, name);

		y += 200;
	}

}

void LogoGameStackItem::Release()
{
	Core::Log("LogoGameStackItem::Release()");
}
