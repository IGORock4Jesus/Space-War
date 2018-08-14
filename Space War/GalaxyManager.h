#pragma once
#include <d3dx9.h>
#include <string>
#include <vector>
#include "Race.h"
#include "json.h"

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

#ifdef _DEBUG
	const char* filename = "galaxies.txt";
#else
	const char* filename = "..\\game\\galaxies.txt";
#endif // _DEBUG

	void Parse(std::vector<char>& data);

public:
	GalaxyManager();
	~GalaxyManager();

	bool Load();
	//int GetGalaxyCount() { if (file) return file->countOfGalaxies; return 0; }
	//std::string GetGalaxyName(int index) { if (!file) return ""; return file->galaxies[index].name; }

	int GetGalaxyCount() { if (!file) return 0; return file.size(); }
	std::string GetGalaxyName(int index) { if (!file) return ""; return file["galaxies"][index]["name"]; }
	std::string GetGalaxyTexturePath(int index) { if (!file) return ""; return file["galaxies"][index]["texture_path"]; }
};

