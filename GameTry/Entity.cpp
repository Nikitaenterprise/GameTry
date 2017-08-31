#include "Entity.h"



Entity::Entity(sf::Image &image, sf::String Name, float X, float Y, float W, float H)
{
	x = X; y = Y; w = W; h = H; name = Name; dx = 0; dy = 0; speed = 0;
	health = 100;
	isLive = true; isMove = false; onGround = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
	std::cout << "Hi! I`m entity\n";
}


Entity::~Entity()
{
	std::cout << "Entity deleted\n";
}

sf::FloatRect Entity::GetRect()
{
	return sf::FloatRect(x, y, w, h);
}