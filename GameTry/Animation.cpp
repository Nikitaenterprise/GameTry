#include "Animation.h"

//Animation::Animation(float _playSpeed)
//{
//	playSpeed = _playSpeed;
//	currentFrame = 0;
//	isPaused = true;
//	
//	std::cout<<"Hi I`m animation class\n";
//}

Animation::Animation()
{
	playSpeed = 0.5;
	currentFrame = 0;
	isPaused = true;
	std::cout << "Hi I`m animation class1\n";
}

Animation::~Animation()
{
	std::cout << "Bye I was animation class\n";
}

void Animation::SetSpriteSheet(sf::Texture & _texture)
{
	texture = _texture;
}

void Animation::PushFrame(sf::IntRect _frame)
{
	frames.push_back(_frame);
	std::cout << "Frame pushed by first push\n";
}

void Animation::PushFrame(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage)
{
	frames.push_back(sf::IntRect(_spriteXInImage, _spriteYInImage, _spriteWInImage, _spriteHInImage));
	std::cout << "Frame pushed by second push\n";
}

const sf::IntRect & Animation::GetFrame(std::size_t n) const
{
	return frames[n];
}

void Animation::SetFrame(std::size_t _frame)
{

}

std::size_t Animation::GetVectorSize()
{
	return frames.size();
}

void Animation::Play()
{
	isPaused = false;
}

void Animation::Pause()
{
	isPaused = true;
}

void Animation::Update(float time)
{
	if (!isPaused)
	{		
		currentTime += time;
		if (currentTime >= playSpeed)
		{
			if (currentFrame + 1 < this->GetVectorSize())
			{
				currentFrame++;
			}
			else
			{
				currentFrame = 0;
				if (!isLooped)
				{
					isPaused = true;
				}
			}
			SetFrame(currentFrame);
		}
	}
}
