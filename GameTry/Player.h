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

	Player(sf::Image &image, sf::String Name, Level &lev, float X, float Y, float W, float H);
	~Player();

	float GetPlayerCoordinateX();
	float GetPlayerCoordinateY();
	void Control();
	void Update(float time);
	void CheckCollisionWithMap(float Dx, float Dy);
	void MouseControl(sf::Event & event, sf::Vector2f & pos);
	void AutoMove(float tempX, float tempY, float time);
	void IntersectionWithEntities(std::list <Entity*>::iterator & it, float time);
};