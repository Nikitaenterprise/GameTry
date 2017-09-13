#include "My_Animation.h"

Animation::Animation()
{
	playSpeed = 150;
	currentTime = 0;
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
	sprite.setTexture(texture);
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

sf::Sprite & Animation::GetFrameSprite(sf::IntRect rect)
{
	sprite.setTextureRect(rect);
	return sprite;
}

void Animation::SetFrame(std::size_t _frame)
{
	currentFrame = _frame;
}

std::size_t Animation::GetVectorSize()
{
	return frames.size();
}

void Animation::IsSpriteReversed(bool state)
{
	if (state)
	{
		sprite.scale(-1, 1);
	}
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
		std::cout << currentTime << " " << currentFrame << " " << playSpeed << " " << time << std::endl;
		if (currentTime >= playSpeed)
		{
			currentTime = 0;
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

//void Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
//{
//	states.transform *= getTransform();
//	states.texture = texture;
//	
//	target.draw(m_vertices, 4, sf::Quads, states);
//}