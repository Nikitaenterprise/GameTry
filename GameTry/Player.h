#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Bird;
class Player : public Entity
{
private:
	
public:
	int playerScore;
	bool isSelect, isShoot;
	bool onPlatform, onLadder;
	enum {left, up, right, down, jump, stay} state;
	float tempX, tempY;//временные переменные для авто перемещения по клику

	Player();
	Player(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage);
	~Player();

	Animation playerStay;
	Animation playerRight;
	Animation playerLeft;
	Animation playerUp;
	Animation playerJump;

	Bird bird;

	float GetPlayerCoordinateX();
	float GetPlayerCoordinateY();
	void Control();
	void Update(float _time);
	void CheckCollisionWithMap(float _dx, float _dy);
	void MouseControl(sf::Event & event, sf::Vector2f & pos);
	void AutoMove(float tempX, float tempY, float _time);
	void IntersectionWithEntities(std::list <Entity*>::iterator & it, float _time);
	void AnimationSetup();
};

#include "Bird.h"