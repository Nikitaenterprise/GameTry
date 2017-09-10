#pragma once
#include <iostream>
#include <vector>
#include "Entity.h"

class Animation
{
public:
	char* name;

	Animation();
	//Animation(std::list<Entity*> & _entities, std::list<Entity*>::iterator & _it, int _numberOfFrames, float _time);
	Animation(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage);
	~Animation();

	std::vector<sf::IntRect> frames;

	void pushFrame(sf::IntRect _frame);
	void pushFrame(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage);
	//sf::Sprite & pop() const;
	int GetVectorSize();
	void Play();
	void Pause();

};

