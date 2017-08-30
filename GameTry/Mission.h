#pragma once
#include <iostream>

int GetCurrentMission(int x)
{
	int mission;
	if (x > 0 && x < 600) mission = 0;
	else if (x > 400) mission = 1;
	return mission;
}

std::string getTextMission(int currentMission)
{

	std::string missionText = "";

	switch (currentMission)//����������� ����� ������ � � ����������� �� ���� ���������� missionText ������������� ��������� �����
	{
	case 0: missionText = "\n��������� ���� � \n���������� � ����"; break;
	case 1: missionText = "\nMission 1\n\n��� ���� ������\n ������, ��\n ���� ������ \n���� ����� ���������\n ... ���-���-��� ..."; break;
	case 2: missionText = "\nMission 2\n ���������� ������\n ���������� �������,\n ����� ������ ������ "; break;
	case 3: missionText = "\n� ��� ����� \n� ���� ��������....."; break;
	}

	return missionText;//�-��� ���������� �����
};