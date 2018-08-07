#include "GalaxyManager.h"
#include "Core.h"
#include <fstream>


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

	/*std::string error;
	auto v = Core::LoadFile("..\\game\\galaxies.txt", &error);
	if (v.size() == 0) {
		MessageBox(0, error.c_str(), "LoadFile(\"..\\game\\galaxies.txt\")", 0);
		return false;
	}*/

	auto galfile = std::ifstream{ filename };
	if (galfile.bad()) return false;

	file = new File;
	galfile >> file->countOfGalaxies;

	if (file->countOfGalaxies != 0) {
		file->galaxies = new File::Galaxy[file->countOfGalaxies];

		for (int g = 0; g < file->countOfGalaxies; g++)
		{
			galfile >> file->galaxies[g].name;
			galfile >> file->galaxies[g].countOfPlanets;
			if (file->galaxies[g].countOfPlanets != 0) {
				file->galaxies[g].planets = new File::Galaxy::Planet[file->galaxies[g].countOfPlanets];

				for (int i = 0; i < file->galaxies[g].countOfPlanets; i++)
				{
					galfile >> file->galaxies[g].planets[i].name;
					galfile >> file->galaxies[g].planets[i].position.x;
					galfile >> file->galaxies[g].planets[i].position.y;
					int race;
					galfile >> race;
					file->galaxies[g].planets[i].race = (Race)race;
				}
			}
		}
	}



	return true;
}
