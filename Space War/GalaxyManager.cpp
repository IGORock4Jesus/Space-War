#include "GalaxyManager.h"
#include "Core.h"
#include <fstream>


void GalaxyManager::Parse(std::vector<char>& data)
{
	file = nlohmann::json::parse(data.data());


}

GalaxyManager::GalaxyManager()
{
}


GalaxyManager::~GalaxyManager()
{
	//if (file) delete file;
}

bool GalaxyManager::Load()
{
	/*if (file) {
		delete file;
		file = nullptr;
	}*/

	auto data{ Core::LoadFile(filename) };

	//auto galfile = std::ifstream{ filename };
	//if (galfile.bad()) return false;

	//file = new File;
	//galfile >> file->countOfGalaxies;

	//if (file->countOfGalaxies != 0) {
	//	file->galaxies = new File::Galaxy[file->countOfGalaxies];

	//	for (int g = 0; g < file->countOfGalaxies; g++)
	//	{
	//		galfile >> file->galaxies[g].name;
	//		galfile >> file->galaxies[g].countOfPlanets;
	//		if (file->galaxies[g].countOfPlanets != 0) {
	//			file->galaxies[g].planets = new File::Galaxy::Planet[file->galaxies[g].countOfPlanets];

	//			for (int i = 0; i < file->galaxies[g].countOfPlanets; i++)
	//			{
	//				galfile >> file->galaxies[g].planets[i].name;
	//				galfile >> file->galaxies[g].planets[i].position.x;
	//				galfile >> file->galaxies[g].planets[i].position.y;
	//				int race;
	//				galfile >> race;
	//				file->galaxies[g].planets[i].race = (Race)race;
	//			}
	//		}
	//	}
	//}

	Parse(data);

	return true;
}


#pragma region GETs

int GalaxyManager::GetGalaxyCount() {
	try { return file["galaxies"].size(); }
	catch (nlohmann::json::type_error ex) { Core::Log(ex.what()); return 0; }
}

std::string GalaxyManager::GetGalaxyName(int index) {
	return file["galaxies"][index]["name"];
}

std::string GalaxyManager::GetGalaxyTexturePath(int index) { 
	return file["galaxies"][index]["texture_path"]; 
}

#pragma endregion