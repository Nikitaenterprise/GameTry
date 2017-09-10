#include "Animation.h"

Animation::Animation()
{
}

//Animation::Animation(std::list<Entity*> & _entities, std::list<Entity*>::iterator & _it, int _numberOfFrames, float _time)
//{
//	static float currentFrame = 0;
//	currentFrame += 0.005*_time;
//	if (currentFrame > _numberOfFrames) currentFrame -= _numberOfFrames;
//	(*_it)->sprite.setTextureRect(sf::IntRect((*_it)->spriteXInImage * int(currentFrame),(*_it)->spriteYInImage, (*_it)->spriteWInImage, (*_it)->spriteHInImage));
//}

Animation::Animation(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage)
{
}

Animation::~Animation()
{
	std::cout << "Hi I`m animation class\n";
}

void Animation::pushFrame(sf::IntRect _frame)
{
	frames.push_back(_frame);
	std::cout << "Frame pushed by first push\n";
}

void Animation::pushFrame(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage)
{
	frames.push_back(sf::IntRect(_spriteXInImage, _spriteYInImage, _spriteWInImage, _spriteHInImage));
	std::cout << "Frame pushed by second push\n";
}

int Animation::GetVectorSize()
{
	return frames.size();
}

void Animation::Play()
{
	std::vector<sf::IntRect>::iterator it;
	for (it = frames.begin(); it != frames.end(); it++)
	{
		
	}
}

void Animation::Pause()
{
}
