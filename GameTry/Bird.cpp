#include "Bird.h"

Bird::Bird() : Player()
{
}

Bird::Bird(sf::Sprite & _sprite, sf::String _name, float _x, float _y) :
	Player()
{
	sprite = _sprite;
	name = _name;
	x = _x;
	y = _y;
	std::cout << "Hi I`m bird\n";
}

Bird::~Bird()
{
}

double Bird::CheckBirdTime()
{
	std::cout << t << std::endl;
	if (t > 3) birdClock.restart();
	return t;
}

void Bird::AnimationSetup()
{
	flyingLeft.SetSpriteSheet(texture);
	sprite.scale(-1, 1);
}

void Bird::CheckPlayerCoordinates(const Player & obj)
{
	/*t = birdClock.getElapsedTime().asSeconds();
	if (t < 100)
	{
		tempX = obj.x;
		tempY = obj.y;
		tempTime = t;
	}
	if ((tempX - obj.x != 0) || (tempY - obj.y != 0)) birdClock.restart();*/
	Following(obj);
}

void Bird::Following(const Player & obj)
{
	dx = obj.x - x;
	dy = obj.y - y;
	x += dx*0.1;
	y += dy*0.1 - 3;
}
