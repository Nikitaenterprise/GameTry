#pragma once
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Entity.h"

class Animation : public sf::Drawable, public sf::Transformable
{
public:

	float playSpeed;
	float currentTime;
	int currentFrame;
	bool isPaused;
	bool isLooped;

	//explicit Animation(float _playSpeed);
	Animation();
	~Animation();

	void virtual draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<sf::IntRect> frames;
	sf::Texture texture;

	void SetSpriteSheet(sf::Texture & _texture);
	void PushFrame(sf::IntRect _frame);
	void PushFrame(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage);
	const sf::IntRect & GetFrame(std::size_t n) const;
	void SetFrame(std::size_t _frame);
	std::size_t GetVectorSize();
	void Play();
	void Pause();
	void Update(float time);
};

