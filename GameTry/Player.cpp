#pragma once
#include "Player.h"

Player::Player(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage) : 
	Entity(_image, _name, _x, _y, _spriteXInImage, _spriteYInImage, _spriteWInImage, _spriteHInImage)
{
	obj = _level.GetAllObjects();//��������������.�������� ��� ������� ��� �������������� ��������� � ������	
	playerScore = 0;
	state = stay;
	isSelect = false;
	isShoot = false;
	if (name == "Player1")
	{
		sprite.setTextureRect(sf::IntRect(spriteXInImage, spriteYInImage, spriteWInImage, spriteHInImage));
	}
	AnimationSetup();
	//std::cout << playerStay.getSize() << std::endl;
	//std::cout << playerRight.getSize() << std::endl;
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
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))))
	{
		state = right;
		speed = 0.1;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))&&(onGround))
	{
		state = up;
		speed = 0.1;
		dy = -0.5;
		onGround = false;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))))
	{
		state = down;
		speed = 0.1;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (onGround))
	{
		state = up;
		dy = -0.2;
		speed = 0.1;
		onGround = false;
	}
	else if (onGround)
	{
		state = stay;
		dx = 0;
		dy = 0;
	}
}

void Player::Update(float _time)
{
	Control();
	switch (state)
	{
	case left:
		dx = -speed;
		currentAnimation = &playerLeft;
		break;
	case up:
		break;
	case right:
		dx = speed;
		currentAnimation = &playerRight;
		break;
	case down:
		break;
	case stay:
		currentAnimation = &playerStay;
		break;
	}
	x += dx*_time;
	CheckCollisionWithMap(dx, 0);
	y += dy*_time;
	CheckCollisionWithMap(0, dy);
	if(!isMove) speed = 0;
	sprite = currentAnimation->GetFrameSprite(currentAnimation->GetFrame(currentAnimation->currentFrame));
	sprite.setPosition(x , y );
	dy += 0.0010*_time;
	currentAnimation->Play();
	currentAnimation->Update(_time);
	//currentAnimation->GetFrame(currentAnimation->currentFrame);
	
	/*AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	animatedSpriteDef = &animatedSprite;
	animatedSprite.setPosition(x, y);*/

}

void Player::CheckCollisionWithMap(float _dx, float _dy)
{
	for (int i = 0; i<obj.size(); i++)//���������� �� ��������
		if (GetRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == "solid")//���� ��������� �����������
			{
				if (_dy>0) { y = obj[i].rect.top - spriteHInImage;  dy = 0; onGround = true; }
				if (_dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (_dx>0) { x = obj[i].rect.left - spriteWInImage; }
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

void Player::IntersectionWithEntities(std::list <Entity*>::iterator & it, float _time)
{
	if ((*it)->GetRect().intersects(this->GetRect()))//���� ������������� ������� ������� ������������ � �������
	{
		if ((*it)->name == "EasyEnemy")
		{
			if ((this->dy>0 && this->onGround == false) || (this->dy>0))
			{
				//���� �������� �� �����,�� ���� ����� �������� 0,����������� �� ���� ���� �����,���� ��� �������� 0
				//��� ���� ��������� � �� ��������
				(*it)->dx = 0; 
				this->dy = -0.2;
				(*it)->health = 0; 
			}
			if ((*it)->dx > 0)
			{
				//���� ���� ���� ������ ����� ����������� ��� � �������������
				(*it)->x = this->x - (*it)->spriteWInImage;
				(*it)->dx *= -1;
				(*it)->sprite.scale(-1, 1);
				(*it)->dy = -0.3;
			}
			else if ((*it)->dx < 0)
			{
				//���� ���� ���� ����� ����� ����������� ��� � �������������
				(*it)->x = this->x + (*it)->spriteWInImage;
				(*it)->dx *= -1;
				(*it)->sprite.scale(-1, 1);
				(*it)->dy = -0.3;
			}
			else
			{
				this->health -= 5;	//����� ���� ������� � ��� ����� � ����� ����
			}
		}
		if ((*it)->name == "SimplePlatform")
		{

			if (this->y + this->spriteHInImage < (*it)->y + (*it)->spriteHInImage)
			{
				this->dx = 0;
				//���� ����� ��������� ���� ���������, �.� ��� ��� ���� ������� (�� �� ��� ��������� ��� �� ���������� � ����������)
				if (this->dy > 0 && this->onGround == false)
				{
					this->x += 2*(*it)->dx*_time;
					this->y = (*it)->y - this->spriteHInImage;
					this->dy = 0;
				}
			}
		}
	}
}

void Player::AnimationSetup()
{
	playerStay.SetSpriteSheet(texture);
	playerStay.PushFrame(sf::IntRect(4, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(48, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(98, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(146, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(194, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(242, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(288, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(338, 18, spriteWInImage, spriteHInImage));
	
	playerRight.SetSpriteSheet(texture);
	playerRight.PushFrame(sf::IntRect(297, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(342, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(387, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(431, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(474, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(521, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(565, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(610, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(656, 102, spriteWInImage, spriteHInImage));

	playerLeft = playerRight;
	playerLeft.IsSpriteReversed(true);

	currentAnimation = &playerStay;
}
