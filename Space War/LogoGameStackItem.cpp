#include "LogoGameStackItem.h"
#include "Core.h"


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

	// ������� ������������� ��� ���� �������� � ��������� �� ��� ������
	for (size_t i = 0; i < galaxyManager.GetGalaxyCount(); i++)
	{

	}

}

void LogoGameStackItem::Release()
{
	Core::Log("LogoGameStackItem::Release()");
}
