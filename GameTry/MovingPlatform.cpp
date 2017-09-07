#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(sf::Image & image, sf::String Name, Level & lvl, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H)
{
	sprite.setTextureRect(sf::IntRect(736, 512, W, H));
	dx = 0.08;
}

void MovingPlatform::Update(float time)
{
	x += dx*time;
	moveTimer += time;
	if (moveTimer > 2000)
	{
		//меняем направление движения  если прошло 2 сек
		dx *= -1;
		moveTimer = 0;
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}


