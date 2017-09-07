#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
private:
	
public:
	int playerScore;
	bool isSelect, isShoot;
	enum {left, up, right, down, jump, stay} state;
	float tempX, tempY;//временные переменные для авто перемещения по клику

	Player(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _w, int _h);
	~Player();

	float GetPlayerCoordinateX();
	float GetPlayerCoordinateY();
	void Control();
	void Update(float _time);
	void CheckCollisionWithMap(float _dx, float _dy);
	void MouseControl(sf::Event & event, sf::Vector2f & pos);
	void AutoMove(float tempX, float tempY, float _time);
	void IntersectionWithEntities(std::list <Entity*>::iterator & it, float time);
};