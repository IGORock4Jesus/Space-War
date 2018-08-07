#pragma once
#include <d3dx9.h>
#include "Race.h"

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
	struct File
	{
		int countOfGalaxies;
		struct Galaxy
		{
			int countOfPlanets;
			struct Planet
			{
				char name[32];
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
	};

	File* file = nullptr;

public:
	GalaxyManager();
	~GalaxyManager();

	bool Load();


};

