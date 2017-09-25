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

void Bird::AnimationSetup()
{
	flyingLeft.SetSpriteSheet(texture);

}

void Bird::setCoordinates(const Player & obj)
{
	this->x = obj.x - obj.spriteWInImage / 2;
	this->y = obj.y - obj.spriteHInImage / 2;
}
