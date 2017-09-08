#pragma once
#include <iostream>
#include "Entity.h"

class Animation
{
public:

	Animation(std::list<Entity*> & _entities, std::list<Entity*>::iterator & _it, int _numberOfFrames, float _time);
	~Animation();
	sf::Sprite & Draw();
};

