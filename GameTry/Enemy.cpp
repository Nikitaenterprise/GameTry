#include "Enemy.h"
4
Enemy::Enemy(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage) : 
	Entity(_image, _name, _x, _y, _spriteXInImage, _spriteYInImage, _spriteWInImage, _spriteHInImage)
{
	obj = _level.GetObjects("solid");
	if (name == "EasyEnemy")
	{
		sprite.setTextureRect(sf::IntRect(spriteXInImage, spriteYInImage, spriteWInImage, spriteHInImage));
		dx = 0.1;//äàåì ñêîðîñòü.ýòîò îáúåêò âñåãäà äâèãàåòñÿ
	}
}

Enemy::~Enemy()
{
	std::cout << "Enemy deleted\n";
}

void Enemy::CheckCollisionWithMap(float _dx, float _dy)
{
	for (int i = 0; i<obj.size(); i++)//ïðîõîäèìñÿ ïî îáúåêòàì
		if (GetRect().intersects(obj[i].rect))//ïðîâåðÿåì ïåðåñå÷åíèå ñ îáúåêòîì
		{
			//if (obj[i].name == "solid")//åñëè âñòðåòèëè ïðåïÿòñòâèå
			{
				if (_dy>0) { y = obj[i].rect.top - spriteHInImage;  dy = 0; onGround = true; }
				if (_dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (_dx>0) { x = obj[i].rect.left - spriteWInImage;  dx = -0.1; sprite.scale(-1, 1); }
				if (_dx<0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
			}
		}
}

void Enemy::Update(float _time)
{
	if (name == "EasyEnemy") //äëÿ ïåðñîíàæà ñ òàêèì èìåíåì ëîãèêà áóäåò òàêîé
	{
		x += dx*_time;
		CheckCollisionWithMap(dx, 0);//îáðàáàòûâàåì ñòîëêíîâåíèå ïî Õ
		y += dy*_time;
		CheckCollisionWithMap(0, dy);
		sprite.setPosition(x + spriteWInImage / 2, y + spriteHInImage / 2); //çàäàåì ïîçèöèþ ñïðàéòà â ìåñòî åãî öåíòðà
		if (health <= 0) { isLive = false; }
		dy += 0.0010*_time;
	}
}

void Enemy::AnimationSetup()
{
}
