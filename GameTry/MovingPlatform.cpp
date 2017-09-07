#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _w, int _h) : Entity(_image, _name, _x, _y, _w, _h)
{
	sprite.setTextureRect(sf::IntRect(736, 512, _w, _h));
	dx = 0.1;
}

void MovingPlatform::Update(float _time)
{
	x += dx*_time;
	moveTimer += _time;
	if (moveTimer > 2000)
	{
		//меняем направление движения  если прошло 2 сек
		dx *= -1;
		moveTimer = 0;
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}


