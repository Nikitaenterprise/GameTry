#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	int direction;

	Bullet(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _w, int _h, int _direction);
	~Bullet();

	void Update(float time);
};

