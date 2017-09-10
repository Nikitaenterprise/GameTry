#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	int direction;

	Bullet(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage, int _direction);
	~Bullet();

	void Update(float _time);
	void AnimationSetup();

};

