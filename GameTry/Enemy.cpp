#include "Enemy.h"

Enemy::Enemy(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage) : 
	Entity(_image, _name, _x, _y, _spriteXInImage, _spriteYInImage, _spriteWInImage, _spriteHInImage)
{
	obj = _level.GetObjects("solid");
	if (name == "EasyEnemy")
	{
		sprite.setTextureRect(sf::IntRect(spriteXInImage, spriteYInImage, spriteWInImage, spriteHInImage));
		dx = 0.1;//даем скорость.этот объект всегда двигается
		AnimationSetup();
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
				if (_dy>0) 
				{ 
					y = obj[i].rect.top - spriteHInImage;
					dy = 0;
					onGround = true;
				}
				if (_dy<0) 
				{ 
					y = obj[i].rect.top + obj[i].rect.height;
					dy = 0;
				}
				if (_dx>0) 
				{ 
					x = obj[i].rect.left - spriteWInImage;
					dx = -0.1;
					//currentAnimation = &enemyLeft;
					//sprite.scale(-1, 1);
				}
				if (_dx<0)
				{ 
					x = obj[i].rect.left + obj[i].rect.width;
					dx = 0.1;
					//currentAnimation = &enemyRight;
					//sprite.scale(-1, 1);
				}
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
		sprite = currentAnimation->GetFrameSprite(currentAnimation->GetFrame(currentAnimation->GetCurrentFrame()));
		sprite.setPosition(x + spriteWInImage / 2, y + spriteHInImage / 2); //задаем позицию спрайта в место его центра
		if (health <= 0) { isLive = false; }
		dy += 0.0010*_time;
		AnimaitonUpdate(_time);
	}
}

void Enemy::AnimationSetup()
{
	enemyRight.SetSpriteSheet(texture);
	enemyRight.SetPlaySpeed(80);
	enemyRight.IsSpriteReversed(false);
	enemyRight.SetOrigin(spriteWInImage, spriteHInImage);
	enemyRight.PushFrame(sf::IntRect(298, 102, spriteWInImage, spriteHInImage));
	enemyRight.PushFrame(sf::IntRect(342, 102, spriteWInImage, spriteHInImage));
	enemyRight.PushFrame(sf::IntRect(387, 102, spriteWInImage, spriteHInImage));
	enemyRight.PushFrame(sf::IntRect(431, 102, spriteWInImage, spriteHInImage));
	enemyRight.PushFrame(sf::IntRect(474, 102, spriteWInImage, spriteHInImage));
	enemyRight.PushFrame(sf::IntRect(521, 102, spriteWInImage, spriteHInImage));
	enemyRight.PushFrame(sf::IntRect(566, 102, spriteWInImage, spriteHInImage));
	enemyRight.PushFrame(sf::IntRect(609, 102, spriteWInImage, spriteHInImage));
	enemyRight.PushFrame(sf::IntRect(656, 102, spriteWInImage, spriteHInImage));

	enemyLeft = enemyRight;
	enemyLeft.IsSpriteReversed(true);

	currentAnimation = &enemyRight;
}

void Enemy::AnimaitonUpdate(float _time)
{
	if (this->dx > 0)
	{
		this->currentAnimation = &enemyRight;
	}
	else if (this->dx < 0)
	{
		this->currentAnimation = &enemyLeft;
	}
	currentAnimation->Play();
	currentAnimation->Update(_time);
}
