#include "Bullet.h"

Bullet::Bullet(sf::Image &image, sf::String Name, Level &lev, float X, float Y, float W, float H, int dir) : Entity(image, Name, X, Y, W, H)
{
	obj = lev.GetObjects("solid");
	x = X; y = Y; w = W; h = H;
	direction = dir;
	isLive = true;
	speed = 0.8;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(1347, 1124, w, h));
	sprite.setOrigin(w / 2, h / 2);
	sprite.setScale(0.5, 0.5);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float time)
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
	x += dx*time;
	y += dy*time;

	for (int i = 0; i < obj.size(); i++) 
	{
		//проход по объектам solid
		if (GetRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
		{
			isLive = false;// то пуля умирает
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}
