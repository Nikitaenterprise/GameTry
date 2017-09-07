#include "Enemy.h"

Enemy::Enemy(sf::Image & image, sf::String Name, Level & lvl, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H)
{
	obj = lvl.GetObjects("solid");
	if (name == "EasyEnemy")
	{
		sprite.setTextureRect(sf::IntRect(4, 19, w, h));
		dx = 0.1;//даем скорость.этот объект всегда двигается
	}
}

Enemy::~Enemy()
{
	std::cout << "Enemy deleted\n";
}

void Enemy::CheckCollisionWithMap(float Dx, float Dy)
{
	//старая проверка

	//for (int i = y / 32; i < (y + h) / 32; i++)
	//	for (int j = x / 32; j<(x + w) / 32; j++)
	//	{
	//		if (TileMap[i][j] == '0')
	//		{
	//			if (Dy>0) { y = i * 32 - h; }
	//			if (Dy<0) { y = i * 32 + 32; }
	//			if (Dx>0) { x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }//разворот персонажа в случае столкновения со стеной
	//			if (Dx<0) { x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }
	//		}
	//	}

	//новая
	for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (GetRect().intersects(obj[i].rect))//проверяем пересечение с объектом
		{
			//if (obj[i].name == "solid")//если встретили препятствие
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
				if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
			}
		}
}

void Enemy::Update(float time)
{
	if (name == "EasyEnemy") //для персонажа с таким именем логика будет такой
	{
		//moveTimer += time;
		//if (moveTimer>3000) { dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
		x += dx*time;
		CheckCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy*time;
		CheckCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0) { isLive = false; }
		dy += 0.0010*time;
	}
}