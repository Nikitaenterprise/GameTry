#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:

	Enemy(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _w, int _h);
	~Enemy();
	void CheckCollisionWithMap(float _dx, float _dy);
	void Update(float _time);
};

