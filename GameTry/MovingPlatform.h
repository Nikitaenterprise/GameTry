#pragma once
#include <iostream>
#include "Entity.h"

class MovingPlatform : public Entity
{
public:
	MovingPlatform(sf::Image &image, sf::String Name, Level &lvl, float X, float Y, int W, int H);
	void Update(float time);
};
