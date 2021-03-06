#include "Bullet.h"

Bullet::Bullet(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage, int _direction) :
	Entity(_image, _name, _x, _y, _spriteXInImage, _spriteYInImage, _spriteWInImage, _spriteHInImage)
{
	obj = _level.GetObjects("solid");
	name = "Bullet";
	direction = _direction;
	isLive = true;
	speed = 0.8;
	texture.loadFromImage(_image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(spriteXInImage, spriteYInImage, spriteWInImage, spriteHInImage));
	sprite.setScale(0.5, 0.5);
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
		//������ �� �������� solid
		if (this->sprite.getGlobalBounds().intersects(obj[i].rect)) //���� ���� ������ ���������� � �����,
		{
			isLive = false;// �� ���� �������
		}
	}
	sprite.setPosition(x + spriteWInImage / 2, y + spriteHInImage / 2);
}

void Bullet::AnimationSetup()
{
}
