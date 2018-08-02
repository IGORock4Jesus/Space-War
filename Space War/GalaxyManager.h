#pragma once
#include <d3dx9.h>
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

