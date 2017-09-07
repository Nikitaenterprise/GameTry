#include "Bullet.h"

Bullet::Bullet(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _w, int _h, int _direction) : Entity(_image, _name, _x, _y, _w, _h)
{
	obj = _level.GetObjects("solid");
	name = "Bullet";
	x = _x; y = _y; w = _w; h = _h;
	image = _image;
	direction = _direction;
	isLive = true;
	speed = 0.8;
	texture.loadFromImage(_image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(1347, 1124, w, h));
	sprite.setScale(0.5, 0.5);
	sprite.setOrigin(w / 2, h / 2);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float _time)
{
	switch (direction)
	{
	case 0:
		dx = -speed;
		dy = 0;
		break;
	case 1:
		dx = 0;
		dy = -speed;
		break;
	case 2:
		dx = speed;
		dy = 0;
		break;
	case 5:
		dx = speed;
		dy = 0;
		break;
	}
	x += dx*_time;
	y += dy*_time;

	for (int i = 0; i < obj.size(); i++) 
	{
		//проход по объектам solid
		if (this->sprite.getGlobalBounds().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
		{
			isLive = false;// то пуля умирает
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}
