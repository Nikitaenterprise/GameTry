#pragma once
#include <SFML\Graphics.hpp>
const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 40;

static sf::String TileMap[MAP_HEIGHT] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0    h     f                            0",
	"0       s                               0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                      f               0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

static void RandomMapGenerate(int number)
{
	int randX, randY;
	srand(time(0));
	int stoneNumber = number;
	while (stoneNumber > 0)
	{
		randX = 1 + rand() % (MAP_WIDTH - 1);
		randY = 1 + rand() % (MAP_HEIGHT - 1);
		if (TileMap[randY][randX] == ' ')
		{
			TileMap[randY][randX] = 's';
			stoneNumber--;
		}
	}
}