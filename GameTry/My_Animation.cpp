#include "My_Animation.h"

Animation::Animation()
{
	playSpeed = 150;
	currentTime = 0;
	currentFrame = 0;
	isPaused = true;
}

Animation::~Animation()
{
}

void Animation::SetSpriteSheet(sf::Texture &_texture)
{
	texture = &_texture;
	sprite.setTexture(*texture);
}

void Animation::SetPlaySpeed(float _playSpeed)
{
	playSpeed = _playSpeed;
}

void Animation::PushFrame(sf::IntRect _frame)
{
	frames.push_back(_frame);
}

void Animation::PushFrame(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage)
{
	frames.push_back(sf::IntRect(_spriteXInImage, _spriteYInImage, _spriteWInImage, _spriteHInImage));
}

void Animation::PushAllFrames(int _spriteStartXInImage, int _spriteStartYInImage, int _spriteWInImage, int _spriteHInImage, int _gapValue, int _numberOfFrames)
{
	for (int i = 0; i < _numberOfFrames; i++)
	{
		frames.push_back(sf::IntRect(_spriteStartXInImage+i*(_gapValue+ _spriteWInImage), _spriteStartYInImage, _spriteWInImage, _spriteHInImage));
	}
}

const sf::IntRect & Animation::GetFrame(std::size_t n) const
{
	return frames[n];
}

std::size_t Animation::GetCurrentFrame()
{
	return currentFrame;
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

void Animation::SetOrigin(int spriteWInImage, int spriteHInImage)
{
	sprite.setOrigin(spriteWInImage / 2, spriteHInImage / 2);
}

void Animation::SetOrigin(int spriteWInImage)
{
	sprite.setOrigin(spriteWInImage / 2, 1);
}

std::size_t Animation::GetVectorSize()
{
	return frames.size();
}

void Animation::IsSpriteReversed(bool state)
{
	if (state)
	{
		isSpriteReversed = state;
	}
	if (!state)
	{
		isSpriteReversed = state;
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
	if (!this->isPaused)
	{		
		this->currentTime += time;
		if (this->currentTime >= this->playSpeed)
		{
			currentTime = 0;
			if (this->currentFrame + 1 < this->GetVectorSize())
			{
				this->currentFrame++;
			}
			else
			{
				this->currentFrame = 0;
				
				if (!this->isLooped)
				{
					this->isPaused = true;
				}
			}
			if (this->isSpriteReversed)
			{
				this->sprite.setScale(-1, 1);
			}
			else if (!isSpriteReversed)
			{
				sprite.setScale(1, 1);
			}
		}
	}
}
