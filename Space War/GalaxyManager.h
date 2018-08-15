#pragma once
#include <d3dx9.h>
#include <string>
#include <vector>
#include "Race.h"
#include "json.h"
#include "Core.h"

// нужно разработать систему загрузки галактики из файла
// корневая папка с галактиками (уровнями) - "galaxies"
// в ней будут папки с уровнями
// каждая папка имеет название - это будет название галактики
// в ней (в папке) будут содержаться:
//	1. картинка галактики, которая будет отображаться в меню выбора галактики
//	2. файл с описаниями планет
// описание файла
// 1. количество планет
// 2. массив планет


class GalaxyManager
{
	/*struct File
	{
		int countOfGalaxies;
		struct Galaxy
		{
			std::string name;
			std::string texturePath;
			int countOfPlanets;
			struct Planet
			{
				std::string name;
				D3DXVECTOR2 position;
				Race race;
			};
			Planet* planets = nullptr;

			~Galaxy()
			{
				if (planets) delete[] planets;
			}
		};
		Galaxy* galaxies = nullptr;

		~File()
		{
			if (galaxies) delete[] galaxies;
		}
	};*/

	//File* file = nullptr;

	nlohmann::json file;

	const char* filename = "..\\game\\galaxies.txt";

	void Parse(std::vector<char>& data);

public:
	GalaxyManager();
	~GalaxyManager();

	bool Load();
	//int GetGalaxyCount() { if (file) return file->countOfGalaxies; return 0; }
	//std::string GetGalaxyName(int index) { if (!file) return ""; return file->galaxies[index].name; }

	int GetGalaxyCount();
	std::string GetGalaxyName(int index);
	std::string GetGalaxyTexturePath(int index);
};

