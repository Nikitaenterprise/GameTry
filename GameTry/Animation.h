#pragma once
#include <iostream>
#include <vector>
#include "Entity.h"

class Animation
{
public:

	char* name;
	float playSpeed;
	float currentTime;
	int currentFrame;
	bool isPaused;
	bool isLooped;

	Animation(char* _name, float _playSpeed);
	Animation();
	~Animation();

	std::vector<sf::IntRect> frames;

	void PushFrame(sf::IntRect _frame);
	void PushFrame(int _spriteXInImage, int _spriteYInImage, int _spriteWInImage, int _spriteHInImage);
	const sf::IntRect & GetFrame(std::size_t n) const;
	void SetFrame(std::size_t _frame);
	std::size_t GetVectorSize();
	void Play();
	void Pause();
	void Update(float time);
};

