#pragma once
#include <iostream>
#include "Entity.h"

class MovingPlatform : public Entity
{
public:
	MovingPlatform(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _w, int _h);
	void Update(float _time);
};
