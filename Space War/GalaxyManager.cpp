#include "GalaxyManager.h"
#include "Core.h"


GalaxyManager::GalaxyManager()
{
}


GalaxyManager::~GalaxyManager()
{
	if (file) delete file;
}

bool GalaxyManager::Load()
{
	if (file) delete file;

	std::string error;
	auto v = Core::LoadFile("..\\game\\galaxies.txt", &error);
	if (v.size() == 0) {
		MessageBox(0, error.c_str(), "LoadFile(\"..\\game\\galaxies.txt\")", 0);
		return false;
	}

	return true;
}
