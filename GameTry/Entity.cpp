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

void IntersectionBetweenEntities(std::list<Entity*>& entities, std::list<Entity*>::iterator & it, std::list<Entity*>::iterator & it2)
{
	//если враги разные
	if ((*it)->GetRect() != (*it2)->GetRect())
	{
		//и два их спрайта пересекаются
		if ((*it)->GetRect().intersects((*it2)->GetRect()) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))
		{
			//тогда расталкиваем их
			(*it)->dx *= -1;
			(*it)->sprite.scale(-1, 1);
		}
	}
}
