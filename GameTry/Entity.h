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

