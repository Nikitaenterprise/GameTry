#pragma once
#include <vector>
#include <iostream>
#include <list>
#include <SFML\Graphics.hpp>
#include "level.h"


class Entity
{
public:
	
	float x, y, w, h, dx, dy, speed;
	float moveTimer;
	int health;
	bool isLive, isMove, onGround;

	sf::String name;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	std::vector<Object> obj;

	Entity(sf::Image & _image, sf::String _name, float _x, float _y, int _w, int _h);
	~Entity();
	sf::FloatRect GetRect();
	virtual void Update(float _time) = 0;
	
};

void IntersectionBetweenEntities(std::list <Entity*> & entities, std::list <Entity*>::iterator & it, std::list <Entity*>::iterator & it2);