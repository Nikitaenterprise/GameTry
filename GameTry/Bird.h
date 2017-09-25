#pragma once
#include "Player.h"

class Bird : public Player
{
public:
	Bird();
	Bird(sf::Sprite & _sprite, sf::String _name, float _x, float _y);
	~Bird();

	Animation flyingLeft;

	void AnimationSetup();
	void setCoordinates(const Player & obj);
};

