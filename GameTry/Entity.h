#pragma once
#include <vector>
#include <iostream>
#include <list>
#include <SFML\Graphics.hpp>
#include "map.h"
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

	Entity(sf::Image &image, sf::String Name, float X, float Y, float W, float H);
	~Entity();
	sf::FloatRect GetRect();
	virtual void Update(float time) = 0;
	
};

void IntersectionBetweenEntities(std::list <Entity*> & entities, std::list <Entity*>::iterator & it, std::list <Entity*>::iterator & it2);