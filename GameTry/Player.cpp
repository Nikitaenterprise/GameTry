#pragma once
#include "Player.h"

Player::Player(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _w, int _h) : Entity(_image, _name, _x, _y, _w, _h)
{
	obj = _level.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой	
	playerScore = 0;
	state = stay;
	isSelect = false;
	isShoot = false;
	if (name == "Player1")
	{
		sprite.setTextureRect(sf::IntRect(int(4), int(19), _w, _h)); 
	}
}

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
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (onGround))
	{
		state = up;
		dy = -0.2;
		speed = 0.1;
		onGround = false;
	}
}

void Player::Update(float _time)
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
	x += dx*_time;
	CheckCollisionWithMap(dx, 0);
	y += dy*_time;
	CheckCollisionWithMap(0, dy);
	if(!isMove) speed = 0;
	sprite.setPosition(x + w / 2, y + h / 2);
	dy += 0.0010*_time;
}

void Player::CheckCollisionWithMap(float _dx, float _dy)
{
	for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (GetRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (_dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (_dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (_dx>0) { x = obj[i].rect.left - w; }
				if (_dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
}

void Player::MouseControl(sf::Event & event, sf::Vector2f & pos)
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

void Player::AutoMove(float tempX, float tempY, float _time)
{
	float distance;
	if (isMove)
	{
		distance = sqrt(pow((x - tempX), 2) + pow((y - tempY), 2));
		if (distance >= 2)
		{
			x += 0.1*_time*(tempX - x) / distance;
			y += 0.1*_time*(tempY - y) / distance;
		}
		else
		{
			isMove = false;
		}
	}
}

void Player::IntersectionWithEntities(std::list <Entity*>::iterator & it, float time)
{
	if ((*it)->GetRect().intersects(this->GetRect()))//если прямоугольник спрайта объекта пересекается с игроком
	{
		if ((*it)->name == "EasyEnemy")
		{
			if ((this->dy>0 && this->onGround == false) || (this->dy>0))
			{
				//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
				//или если соскочили а не прыгнули
				(*it)->dx = 0; 
				this->dy = -0.2;
				(*it)->health = 0; 
			}
			if ((*it)->dx > 0)
			{
				//если враг идет вправо тогда отталкиваем его и останавливаем
				(*it)->x = this->x - (*it)->w;
				(*it)->dx *= -1;
				(*it)->sprite.scale(-1, 1);
				(*it)->dy = -0.3;
			}
			else if ((*it)->dx < 0)
			{
				//если враг идет влево тогда отталкиваем его и останавливаем
				(*it)->x = this->x + (*it)->w;
				(*it)->dx *= -1;
				(*it)->sprite.scale(-1, 1);
				(*it)->dy = -0.3;
			}
			else
			{
				this->health -= 5;	//иначе враг подошел к нам сбоку и нанес урон
			}
		}
		if ((*it)->name == "SimplePlatform")
		{

			if (this->y + this->h < (*it)->y + (*it)->h)
			{
				this->dx = 0;
				//если игрок находится выше платформы, т.е это его ноги минимум (тк мы уже проверяли что он столкнулся с платформой)
				if (this->dy > 0 && this->onGround == false)
				{
					this->x += (*it)->dx*time;
					//this->dx += (*it)->dx;
					this->y = (*it)->y - this->h;
					this->dy = 0;
					//this->onGround = true;
				}
			}
		}
	}
}