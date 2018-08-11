#pragma once
#include <d3dx9.h>
#include <string>
#include "Race.h"

// ����� ����������� ������� �������� ��������� �� �����
// �������� ����� � ����������� (��������) - "galaxies"
// � ��� ����� ����� � ��������
// ������ ����� ����� �������� - ��� ����� �������� ���������
// � ��� (� �����) ����� �����������:
//	1. �������� ���������, ������� ����� ������������ � ���� ������ ���������
//	2. ���� � ���������� ������
// �������� �����
// 1. ���������� ������
// 2. ������ ������


class GalaxyManager
{
	struct File
	{
		int countOfGalaxies;
		struct Galaxy
		{
			char name[32];
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
#ifdef _DEBUG
	const char* filename = "galaxies.txt";
#else
	const char* filename = "..\\game\\galaxies.txt";
#endif // _DEBUG

public:
	GalaxyManager();
	~GalaxyManager();

	bool Load();
	int GetGalaxyCount() { if (file) return file->countOfGalaxies; return 0; }
	std::string GetGalaxyName(int index) { if (!file) return ""; return file->galaxies[index].name; }
};

