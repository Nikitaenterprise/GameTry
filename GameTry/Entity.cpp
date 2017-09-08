#include "Entity.h"

Entity::Entity(sf::Image & _image, sf::String _name, float _x, float _y, int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage)
{
	x = _x; y = _y; 
	spriteXInImage = _spriteXInImage; spriteYInImage = _spriteYInImage;
	spriteWInImage = _spriteWInImage; spriteHInImage = _spriteHInImage;
	name = _name; dx = 0; dy = 0; speed = 0;
	health = 100;
	isLive = true; isMove = false; onGround = false;
	texture.loadFromImage(_image);
	sprite.setTexture(texture);
	sprite.setOrigin(spriteWInImage / 2, spriteHInImage / 2);
	std::cout << "Hi! I`m entity\n";
}


Entity::~Entity()
{
	std::cout << "Entity deleted\n";
}

sf::FloatRect Entity::GetRect()
{
	return sf::FloatRect(x, y, spriteWInImage, spriteHInImage);
}

void IntersectionBetweenEntities(std::list<Entity*> & entities, std::list<Entity*>::iterator & it, std::list<Entity*>::iterator & it2)
{
	//если энтити разные
	if ((*it)->GetRect() != (*it2)->GetRect())
	{
		//спрайты пересекаются причем это враги
		if ((*it)->GetRect().intersects((*it2)->GetRect()) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))
		{
			//тогда расталкиваем их
			(*it)->dx *= -1;
			(*it)->sprite.scale(-1, 1);
		}
		//спрайты пересекаются причем это пуля и враг	
		if ((*it)->sprite.getGlobalBounds().intersects((*it2)->sprite.getGlobalBounds()) && ((*it)->name == "Bullet") && ((*it2)->name == "EasyEnemy"))
		{
			//убиваем пулю, врагу -50 здоровья
			(*it)->isLive = false;
			(*it2)->health -= 50;
			//врага откидываем и подбрасываем
			if ((*it)->dx > 0)
			{
				(*it2)->dx += 0.2;
				(*it2)->dy -= 0.2;
			}
			if ((*it)->dx < 0)
			{
				(*it2)->dx -= 0.2;
				(*it2)->dy -= 0.2;
			}

		}
	}
}
