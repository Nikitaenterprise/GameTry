#pragma once
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy(sf::Image &image, sf::String Name, Level &lvl, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H)
	{
		obj = lvl.GetObjects("solid");
		if (name == "EasyEnemy") 
		{
			sprite.setTextureRect(sf::IntRect(4, 19, w, h));
			dx = 0.1;//даем скорость.этот объект всегда двигается
		}
	}
	~Enemy();
	void CheckCollisionWithMap(float Dx, float Dy);
	void Update(float time);
};

