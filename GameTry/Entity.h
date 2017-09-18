#pragma once
#include <vector>
#include <iostream>
#include <list>
#include <SFML\Graphics.hpp>
#include "level.h"
#include "My_Animation.h"
//#include "AnimatedSprite.h"


class Entity
{
public:
	
	float x, y, dx, dy, speed;
	int spriteXInImage, spriteYInImage, spriteWInImage, spriteHInImage;
	float moveTimer;
	int health;
	bool isLive, isMove, onGround;

	Animation *currentAnimation;

	sf::String name;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	std::vector<Object> obj;

	Entity(sf::Image & _image, sf::String _name, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage);
	~Entity();
	sf::FloatRect GetRect();
	virtual void Update(float _time) = 0;
	virtual void AnimationSetup() = 0;
};

void IntersectionBetweenEntities(std::list <Entity*> & entities, std::list <Entity*>::iterator & it, std::list <Entity*>::iterator & it2);