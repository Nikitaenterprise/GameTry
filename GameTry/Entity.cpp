#include "Entity.h"

Entity::Entity(sf::Image & _image, sf::String _name, float _x, float _y, int _w, int _h)
{
	x = _x; y = _y; w = _w; h = _h; name = _name; dx = 0; dy = 0; speed = 0;
	health = 100;
	isLive = true; isMove = false; onGround = false;
	texture.loadFromImage(_image);
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

void IntersectionBetweenEntities(std::list<Entity*> & entities, std::list<Entity*>::iterator & it, std::list<Entity*>::iterator & it2)
{
	//���� ������ ������
	if ((*it)->GetRect() != (*it2)->GetRect())
	{
		//������� ������������ ������ ��� �����
		if ((*it)->GetRect().intersects((*it2)->GetRect()) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))
		{
			//����� ������������ ��
			(*it)->dx *= -1;
			(*it)->sprite.scale(-1, 1);
		}
		//������� ������������ ������ ��� ���� � ����	
		if ((*it2)->GetRect().intersects((*it)->GetRect()) && ((*it)->name == "Bullet") && ((*it2)->name == "EasyEnemy"))
		{
			//������� ����, ����� -50 ��������
			(*it)->isLive = false;
			(*it2)->health -= 50;
		}
	}
}
