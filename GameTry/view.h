#pragma once
#include <SFML\Graphics.hpp>

sf::View view;

void GetPlayerCoordinatesForView(float x, float y)
{
	float tempX = x; float tempY = y;
 
	if (x < 320) tempX = 320;//������� �� ���� ����� �������
	if (y < 240) tempY = 240;//������� �������
	if (y > 700) tempY = 700;//������ �������	
 
	view.setCenter(tempX, tempY); 
}

void MoveViewMap(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) view.move(float(-0.1*time), 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) view.move(0, float(-0.1*time));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) view.move(float(0.1*time), 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) view.move(0, float(0.1*time));
}

void ChangeViewMap(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) view.rotate(float(0.1*time));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) view.rotate(float(-0.1*time));
}
