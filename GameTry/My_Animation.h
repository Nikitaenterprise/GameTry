#pragma once
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>

class Animation
{
public:

	float playSpeed;
	float currentTime;
	int currentFrame;
	bool isPaused;
	bool isLooped;

	Animation();
	~Animation();
	
	std::vector<sf::IntRect> frames;
	sf::Texture texture;
	sf::Sprite sprite;

	void SetSpriteSheet(sf::Texture & _texture);
	void PushFrame(sf::IntRect _frame);
	void PushFrame(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage);
	const sf::IntRect & GetFrame(std::size_t n) const;
	sf::Sprite & GetFrameSprite(sf::IntRect rect);
	void SetFrame(std::size_t _frame);
	std::size_t GetVectorSize();
	void IsSpriteReversed(bool state);

	void Play();
	void Pause();
	void Update(float time);
	//void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

