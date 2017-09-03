#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	int direction;

	Bullet(sf::Image &image, sf::String Name, Level &lev, float X, float Y, float W, float H, int state);
	~Bullet();

	void Update(float time);
};

