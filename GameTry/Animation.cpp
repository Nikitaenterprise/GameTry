#include "Animation.h"

Animation::Animation(std::list<Entity*> & _entities, std::list<Entity*>::iterator & _it, int _numberOfFrames, float _time)
{
	static float currentFrame = 0;
	currentFrame += 0.005*_time;
	if (currentFrame > _numberOfFrames) currentFrame -= _numberOfFrames;
	(*_it)->sprite.setTextureRect(sf::IntRect((*_it)->spriteXInImage * int(currentFrame),(*_it)->spriteYInImage, (*_it)->spriteWInImage, (*_it)->spriteHInImage));
}

Animation::~Animation()
{
}
