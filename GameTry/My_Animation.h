#pragma once
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>

class Animation
{
public:

	Animation();
	~Animation();

	void SetSpriteSheet(sf::Texture & _texture);
	void SetPlaySpeed(float _playSpeed);
	void PushFrame(sf::IntRect _frame);
	void PushFrame(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage);
	void PushAllFrames(int _spriteStartXInImage, int _spriteStartYInImage, int _spriteWInImage, int _spriteHInImage, int _gapValue, int _numberOfFrames);
	const sf::IntRect & GetFrame(std::size_t n) const;
	std::size_t GetCurrentFrame();
	sf::Sprite & GetFrameSprite(sf::IntRect rect);
	void SetFrame(std::size_t _frame);
	std::size_t GetVectorSize();
	void IsSpriteReversed(bool state);

	void Play();
	void Pause();
	void Update(float time);

private:

	float playSpeed;
	float currentTime;
	int currentFrame;
	bool isPaused;
	bool isLooped;
	bool isSpriteReversed;
	std::vector<sf::IntRect> frames;
	sf::Texture *texture;
	sf::Sprite sprite;
};

