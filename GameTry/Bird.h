#pragma once
#include "Player.h"

class Bird : public Player
{
public:
	Bird();
	Bird(sf::Sprite & _sprite, sf::String _name, float _x, float _y);
	~Bird();

	Animation flyingLeft;
	sf::Clock birdClock;

	float t; 
	float tempX, tempY, tempTime;

	double CheckBirdTime();
	void AnimationSetup();
	void CheckPlayerCoordinates(const Player & obj);
	void Following(const Player & obj);
};

