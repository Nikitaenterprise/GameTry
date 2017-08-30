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

	switch (currentMission)//принимается номер миссии и в зависимости от него переменной missionText присваивается различный текст
	{
	case 0: missionText = "\nНачальный этап и \nинструкции к игре"; break;
	case 1: missionText = "\nMission 1\n\nВот твоя первая\n миссия, на\n этом уровне \nтебе стоит опасаться\n ... бла-бла-бла ..."; break;
	case 2: missionText = "\nMission 2\n Необходимо решить\n логическую задачку,\n чтобы пройти дальше "; break;
	case 3: missionText = "\nИ так далее \nи тому подобное....."; break;
	}

	return missionText;//ф-ция возвращает текст
};