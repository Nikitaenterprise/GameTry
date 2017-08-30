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
	bool isSelect;
	enum {left, up, right, down, jump, stay} state;
	float tempX, tempY;//��������� ���������� ��� ���� ����������� �� �����

	Player(sf::Image &image, sf::String Name, Level &lev, float X, float Y, float W, float H) : Entity(image, Name, X, Y, W, H)
	{
		obj = lev.GetAllObjects();//��������������.�������� ��� ������� ��� �������������� ��������� � ������	
		playerScore = 0;
		state = stay;
		isSelect = false;	
		if (name == "Player1")
		{
			sprite.setTextureRect(sf::IntRect(int(4), int(19), w, h)); //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
		}
	};
	~Player();

	float GetPlayerCoordinateX();
	float GetPlayerCoordinateY();
	void Control();
	void Update(float time);
	void CheckCollisionWithMap(float Dx, float Dy);
	void MouseControl(sf::Event &event, sf::Vector2f &pos);
	void AutoMove(float tempX, float tempY, float time);
};