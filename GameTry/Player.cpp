#pragma once
#include "Player.h"

Player::~Player()
{
}

float Player::GetPlayerCoordinateX()
{
	return x;
}

float Player::GetPlayerCoordinateY()
{
	return y;
}

void Player::Control()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))))
	{
		state = left;
		speed = 0.1;
		//CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
		//if (CurrentFrame > 3) CurrentFrame -= 3; // если пришли к третьему кадру - откидываемся назад.
		//player1.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))))
	{
		state = right;
		speed = 0.1;
		//CurrentFrame += 0.005*time;
		//if (CurrentFrame > 3) CurrentFrame -= 3;
		//player1.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 192, 96, 96));
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))&&(onGround))
	{
		state = up;
		speed = 0.1;
		dy = -0.5;
		onGround = false;
		//CurrentFrame += 0.005*time;
		//if (CurrentFrame > 3) CurrentFrame -= 3;
		//player1.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 306, 96, 96));
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))))
	{
		state = down;
		speed = 0.1;
		//CurrentFrame += 0.005*time;
		//if (CurrentFrame > 3) CurrentFrame -= 3;
		//player1.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 6, 96, 96));
	}
	
}

void Player::Update(float time)
{
	Control();
	switch (state)
	{
	case left:
		dx = -speed;
		break;
	case up:
		break;
	case right:
		dx = speed;
		break;
	case down:
		break;
	case stay:
		break;
	}
	x = x + dx*time;
	CheckCollisionWithMap(dx, 0);
	y = y + dy*time;
	CheckCollisionWithMap(0, dy);
	if(!isMove) speed = 0;
	sprite.setPosition(x + w / 2, y + h / 2);
	dy += 0.0010*time;
}

void Player::CheckCollisionWithMap(float Dx, float Dy)
{
	//старая проверка на столкновения
	/*for (int i = y / 32; i < (y + h) / 32; i++)
	{
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')
			{
				if (Dx < 0) x = 32 * j + 32;
				if (Dy < 0) { y = 32 * i + 32; dy = 0; }
				if (Dx > 0) x = 32 * j - w;
				if (Dy > 0) { y = 32 * i - h; dy = 0; onGround = true; }
				else { onGround = false; }
			}
			if (TileMap[i][j] == 's')
			{
				std::cout << "Stone" << std::endl;
				TileMap[i][j] = ' ';
				playerScore++;
				std::cout << "PlayerScore = " << playerScore << std::endl;
				RandomMapGenerate(1);
			}
			if (TileMap[i][j] == 'h')
			{
				std::cout << "Heart" << std::endl;
				health += 20;
				TileMap[i][j] = ' ';
				if (health >= 100) health = 100;
			}
			if (TileMap[i][j] == 'f')
			{
				std::cout << "Flower" << std::endl;
				health -= 20;
				TileMap[i][j] = ' ';
				if (health <= 0)
				{
					health = 0;
					isLive = false;
					std::cout << "Die" << std::endl;
				}
			}
		}
	}*/
	//новая
	for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (GetRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0) { x = obj[i].rect.left - w; }
				if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
}

void Player::MouseControl(sf::Event &event, sf::Vector2f &pos)
{
	if (sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left)
		{
			if (sprite.getGlobalBounds().contains(pos.x, pos.y))
			{
				sprite.setColor(sf::Color::Green);
				isSelect = true;
			}
		}
	}
	if (isSelect)
	{
		if (sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Right)
			{
				dx = pos.x - sprite.getPosition().x;
				//std::cout << "pos.x = " << pos.x << " " << "dx = " << dx << "\n";
				dy = pos.y - sprite.getPosition().y;
				float setRotation = (atan2(dy, dx)) * 180 / 3.14;
				sprite.setRotation(setRotation);
				isMove = true;
				isSelect = false;
				sprite.setColor(sf::Color::White);
				tempX = pos.x;
				tempY = pos.y;
				std::cout << setRotation << "\n";
			}
		}
	}
}

void Player::AutoMove(float tempX, float tempY, float time)
{
	float distance;
	if (isMove)
	{
		distance = sqrt(pow((x - tempX), 2) + pow((y - tempY), 2));
		if (distance >= 2)
		{
			x += 0.1*time*(tempX - x) / distance;
			y += 0.1*time*(tempY - y) / distance;
		}
		else
		{
			isMove = false;
		}
	}
}
