#pragma once
#include "Player.h"

Player::Player()
{
}

Player::Player(sf::Image & _image, sf::String _name, Level & _level, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage) :
	Entity(_image, _name, _x, _y, _spriteXInImage, _spriteYInImage, _spriteWInImage, _spriteHInImage)
{
	obj = _level.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой	
	playerScore = 0;
	state = stay;
	isSelect = false;
	isShoot = false;
	if (name == "Player1")
	{
		sprite.setTextureRect(sf::IntRect(spriteXInImage, spriteYInImage, spriteWInImage, spriteHInImage));
	}
	AnimationSetup();

	bird = new Bird;
	bird->texture.loadFromFile("images/bird.png");
	bird->sprite.setTexture(bird->texture);
	bird->sprite.setScale(0.2, 0.2);
	bird->AnimationSetup();
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
		speed = static_cast<float>(0.1);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))))
	{
		state = right;
		speed = static_cast<float>(0.1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&(onGround||onPlatform))
	{
		state = jump;
		dy = -0.5;
		onGround = false;
	}
	else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && onLadder)
	{
		y -= float(1.0);
		dy = float(0);
		state = up;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))))
	{
		state = down;
		speed = static_cast<float>(0.1);
	}
	else if (onGround)
	{
		state = stay;
		dx = 0;
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
	case jump:
		currentAnimation = &playerJump;
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
	case up:
		currentAnimation = &playerUp;
		break;
	}
	if (!onGround) std::cout << playerJump.GetCurrentFrame() << std::endl;
	x += dx*_time;
	CheckCollisionWithMap(dx, 0);
	y += dy*_time;
	CheckCollisionWithMap(0, dy);
	if(!isMove) speed = 0;
	sprite = currentAnimation->GetFrameSprite(currentAnimation->GetFrame(currentAnimation->GetCurrentFrame()));
	sprite.setPosition(x + spriteWInImage / 2, y + spriteHInImage / 2);
	
	bird->setCoordinates(*this);
	bird->sprite.setPosition(bird->x, bird->y);
	
	dy += 0.0010*_time;
	currentAnimation->Play();
	currentAnimation->Update(_time);
	onPlatform = false;
}

void Player::CheckCollisionWithMap(float _dx, float _dy)
{
	for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (GetRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (_dy>0) 
				{ 
					this->y = obj[i].rect.top - spriteHInImage;
					this->dy = 0;
					this->onGround = true;
				}
				if (_dy<0) 
				{ 
					this->y = obj[i].rect.top + obj[i].rect.height;
					this->dy = 0;
				}
				if (_dx>0) 
				{
					this->x = obj[i].rect.left - spriteWInImage;
				}
				if (_dx<0) 
				{ 
					this->x = obj[i].rect.left + obj[i].rect.width;
				}
			}
			if (obj[i].name == "ladder") onLadder = true;
			if (obj[i].name != "ladder") onLadder = false;
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
	if ((*it)->GetRect().intersects(this->GetRect()))//если прямоугольник спрайта объекта пересекается с игроком
	{
		if ((*it)->name == "EasyEnemy")
		{
			if ((this->dy>0 && this->onGround == false) || (this->dy>0))
			{
				//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
				//или если соскочили а не прыгнули
				(*it)->dx = 0; 
				this->dy = static_cast<float>(-0.2);
				(*it)->health = 0; 
			}
			if ((*it)->dx > 0)
			{
				//если враг идет вправо тогда отталкиваем его и останавливаем
				(*it)->x = this->x - (*it)->spriteWInImage;
				(*it)->dx *= -1;
				(*it)->sprite.scale(-1, 1);
				(*it)->dy = static_cast<float>(-0.3);
			}
			else if ((*it)->dx < 0)
			{
				//если враг идет влево тогда отталкиваем его и останавливаем
				(*it)->x = this->x + (*it)->spriteWInImage;
				(*it)->dx *= -1;
				(*it)->sprite.scale(-1, 1);
				(*it)->dy = static_cast<float>(-0.3);
			}
			else
			{
				this->health -= 5;	//иначе враг подошел к нам сбоку и нанес урон
			}
		}
		
		if ((*it)->name == "SimplePlatform")
		{
			if (this->y + this->spriteHInImage < (*it)->y + (*it)->spriteHInImage*2)
			{
				//если игрок находится выше платформы, т.е это его ноги минимум (тк мы уже проверяли что он столкнулся с платформой)
				if (this->y > 0 && !this->onGround)
				{
					this->x += 2*(*it)->dx*_time;
					this->dx = 0;
					this->y = (*it)->y - this->spriteHInImage;
					this->dy = 0;
					this->state = stay;
					onPlatform = true;
				}
			}
		}
	}
}

void Player::AnimationSetup()
{
	playerStay.SetSpriteSheet(texture);
	playerStay.IsSpriteReversed(false);
	playerStay.SetOrigin(spriteWInImage, spriteHInImage);
	playerStay.PushFrame(sf::IntRect(4, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(52, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(98, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(146, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(194, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(242, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(288, 18, spriteWInImage, spriteHInImage));
	playerStay.PushFrame(sf::IntRect(336, 18, spriteWInImage, spriteHInImage));
	
	playerRight.SetSpriteSheet(texture);
	playerRight.SetPlaySpeed(80);
	playerRight.IsSpriteReversed(false);
	playerRight.SetOrigin(spriteWInImage, spriteHInImage);
	playerRight.PushFrame(sf::IntRect(298, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(342, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(387, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(431, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(474, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(521, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(566, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(609, 102, spriteWInImage, spriteHInImage));
	playerRight.PushFrame(sf::IntRect(656, 102, spriteWInImage, spriteHInImage));

	playerLeft = playerRight;
	playerLeft.IsSpriteReversed(true);

	playerUp.SetSpriteSheet(texture);
	playerUp.SetPlaySpeed(80);
	playerUp.PushFrame(sf::IntRect(303, 440, 41, 48));
	playerUp.PushFrame(sf::IntRect(345, 440, 41, 48));
	playerUp.PushFrame(sf::IntRect(384, 440, 41, 48));
	playerUp.PushFrame(sf::IntRect(426, 440, 41, 48));
	playerUp.PushFrame(sf::IntRect(469, 440, 41, 48));
	playerUp.PushFrame(sf::IntRect(510, 440, 41, 48));

	playerJump.SetSpriteSheet(texture);
	playerJump.SetPlaySpeed(110);
	playerJump.IsSpriteReversed(false);
	playerJump.SetOrigin(20, 53);
	playerJump.PushFrame(sf::IntRect(10, 338, 20, 53));
	playerJump.PushFrame(sf::IntRect(39, 338, 20, 53));
	playerJump.PushFrame(sf::IntRect(65, 338, 20, 53));
	playerJump.PushFrame(sf::IntRect(91, 338, 20, 53));
	playerJump.PushFrame(sf::IntRect(116, 338, 20, 53));
	playerJump.PushFrame(sf::IntRect(142, 338, 20, 53));
	playerJump.PushFrame(sf::IntRect(168, 338, 20, 53));
	playerJump.PushFrame(sf::IntRect(197, 338, 30, 53));
	playerJump.PushFrame(sf::IntRect(226, 338, 30, 53));
	playerJump.PushFrame(sf::IntRect(258, 338, 34, 53));
	playerJump.PushFrame(sf::IntRect(293, 338, 34, 53));

	currentAnimation = &playerJump;
}
