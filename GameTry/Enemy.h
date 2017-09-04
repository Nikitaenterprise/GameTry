#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:

	Enemy(sf::Image &image, sf::String Name, Level &lvl, float X, float Y, int W, int H);
	~Enemy();
	void CheckCollisionWithMap(float Dx, float Dy);
	void Update(float time);
};

