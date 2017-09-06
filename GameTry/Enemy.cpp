#include "Enemy.h"

Enemy::Enemy(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _w, int _h) : Entity(_image, _name, _x, _y, _w, _h)
{
	obj = _level.GetObjects("solid");
	if (name == "EasyEnemy")
	{
		sprite.setTextureRect(sf::IntRect(4, 19, _w, _h));
		dx = 0.1;//даем скорость.этот объект всегда двигается
	}
}

Enemy::~Enemy()
{
	std::cout << "Enemy deleted\n";
}

void Enemy::CheckCollisionWithMap(float _dx, float _dy)
{
	for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (GetRect().intersects(obj[i].rect))//проверяем пересечение с объектом
		{
			//if (obj[i].name == "solid")//если встретили препятствие
			{
				if (_dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (_dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (_dx>0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
				if (_dx<0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
			}
		}
}

void Enemy::Update(float _time)
{
	if (name == "EasyEnemy") //для персонажа с таким именем логика будет такой
	{
		x += dx*_time;
		CheckCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy*_time;
		CheckCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0) { isLive = false; }
		dy += 0.0010*_time;
	}
}