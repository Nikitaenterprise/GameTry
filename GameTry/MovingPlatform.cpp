#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage) : 
	Entity(_image, _name, _x, _y, _spriteXInImage, _spriteYInImage, _spriteWInImage, _spriteHInImage)
{
	sprite.setTextureRect(sf::IntRect(spriteXInImage, spriteYInImage, spriteWInImage, spriteHInImage));
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
	sprite.setPosition(x + spriteWInImage / 2, y + spriteHInImage / 2);
}


