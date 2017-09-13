#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "MovingPlatform.h"
#include "Bullet.h"
#include "Animation.h"

#include "level.h"
#include "view.h"

#include "Mission.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	float CurrentFrame = 0;
	bool showMissionText = true;
	float timeOfGame;
	bool isMove = false; 
	float dx, dy;
	float tempX, tempY, distance;

	sf::Clock clock;
	sf::Clock gameTimeClock;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);
	view.reset(sf::FloatRect(0, 0, 640, 480));

	Level level;
	level.LoadFromFile("map.tmx");

	sf::Font font;
	font.loadFromFile("cursive/CyrilicOld.TTF");
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

	sf::Font health;
	health.loadFromFile("cursive/CyrilicOld.TTF");
	sf::Text health_text;
	health_text.setFont(health);
	health_text.setFillColor(sf::Color::Blue);
	health_text.setStyle(sf::Text::Bold);

	sf::Image hero_image;
	hero_image.loadFromFile("images/MilesTailsPrower.gif");
	hero_image.createMaskFromColor(sf::Color::Black, 0);

	sf::Image texture_image;
	texture_image.loadFromFile("images/DungeonCrawlTileset.png");

	Object player = level.GetObject("player");

	std::list <Entity*> entities;
	std::list <Entity*>::iterator it;//�������� ��� ������
	std::list <Entity*>::iterator it2;//������ ��������

	std::vector<Object> e;//������ ��� �������� ������, �������� � �������

	//�������� ������
	e = level.GetObjects("enemy");	
	for (int i = 0; i < e.size(); i++)
	{
		entities.push_back(new Enemy(hero_image, "EasyEnemy", level, e[i].rect.left, e[i].rect.top, 4, 19, 40, 30));
	}

	//�������� ��������
	e = level.GetObjects("MovingPlatform");
	for (int i = 0; i < e.size(); i++)
	{
		entities.push_back(new MovingPlatform(texture_image, "SimplePlatform", level, e[i].rect.left, e[i].rect.top, 736, 512, 32 * 4, 32));
	}

	Player player1(hero_image, "Player1", level, player.rect.left, player.rect.top, 4, 19, 40, 30);

	sf::Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(sf::Color(0, 0, 0));
	sf::Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	sf::Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(sf::IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.6f, 0.6f);//���� ��������� ��������, => ������ ���� ������

	while (window.isOpen())
	{
		
		float time = clock.getElapsedTime().asMicroseconds();
		if (player1.isLive) timeOfGame= gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 800;

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//�������� ����� �������
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			//player1.MouseControl(event, pos);
			//player1.AutoMove(player1.tempX, player1.tempY, time);

			if (event.type == sf::Event::KeyPressed)//������� ������� �������
				if (event.key.code == sf::Keyboard::Tab) //���� ������� ���
				{
					switch (showMissionText) //�������������, ����������� �� ���������� ���������� showMissionText
					{
					case true:
					{
						std::ostringstream playerHealthString;//������ �������� ������
						playerHealthString << player1.health; //������� � ������ �������� 
						std::ostringstream task;//������ ������ ������
						task << getTextMission(GetCurrentMission(player1.GetPlayerCoordinateX()));//���������� ������� GetTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
						text.setString("��������: " + playerHealthString.str() + "\n" + task.str());//������
						text.setScale(0.7f, 0.7f);
						text.setPosition(view.getCenter().x + 125, view.getCenter().y - 140);//������� ����� ����� ���������� �����
						s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//������� ���� ��� �����
						showMissionText = false;//��� ������ ��������� ������ ��� ��� �� ������ �� ������
						break;//������� , ����� �� ��������� ������� "false" (������� ����)
					}
					case false:
					{
						text.setString("");//���� �� ������ ������� ���, �� ���� ���� ����� ������
						showMissionText = true;// � ��� ������ ��������� ����� ������ ������� ��� � �������� ����� �� �����
						break;
					}
					}
				}

			//��������
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					//���� ����������, �� ���������� ����. enum �������� ��� int 
					std::cout << player1.state << std::endl;
					entities.push_back(new Bullet(texture_image, "Bullet", level, player1.x, player1.y, 1347, 1124, 32, 32, player1.state));
				}
			}

			if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				entities.push_back(new Enemy(hero_image, "EasyEnemy", level, pos.x, pos.y, 4, 19, 40, 30));
			}

		}

		if (player1.isLive)
		{
			GetPlayerCoordinatesForView(player1.GetPlayerCoordinateX(), player1.GetPlayerCoordinateY());
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);//������� � ������ ���������� ���� ������������ ���� (�,�)
			/*if (localPosition.x < 3) view.move(time*-0.5, 0);
			else if (localPosition.x > window.getSize().x - 3) view.move(time*0.5, 0);
			else if (localPosition.y < 3) view.move(0, time*-0.5);
			else if (localPosition.y > window.getSize().y - 3) view.move(0, time*0.5);*/	
		}
		
		player1.Update(time);
		for (it = entities.begin(); it != entities.end(); it++)
		{
			//�������� ���� ������ �� ������������
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				IntersectionBetweenEntities(entities, it, it2);				
			}
			//�������� ������ � ����� �� ������������
			player1.IntersectionWithEntities(it, time);
		}
		for (it = entities.begin(); it != entities.end();)
		{
			Entity *b = *it;
			b->Update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->isLive == false) 
			{
				// ���� ���� ������ �����, �� ������� ���
				it = entities.erase(it); 
				delete b; 
			}
			else it++;//� ���� ���������� � ���� �������. ��� ������ �� ����� ��������� ������
		}
		//player1.animatedSpriteDef->update();
		//enemy1.Update(time);
		MoveViewMap(time);
		ChangeViewMap(time);
		window.setView(view);
		window.clear(sf::Color(128, 106, 89));
		
		level.Draw(window);

		/*std::ostringstream playerScoreString;
		playerScoreString << player1.playerScore;
		text.setString("���� : " + playerScoreString.str());
		text.setPosition(view.getCenter().x + 180, view.getCenter().y + 180);*/

		/*std::ostringstream playerHealthString;
		playerHealthString << player1.health;
		std::ostringstream playerTimeOfGame;
		playerTimeOfGame << timeOfGame;
		health_text.setString("����� : " + playerHealthString.str() + "\nTime of game : " + playerTimeOfGame.str());
		health_text.setPosition(view.getCenter().x - 180, view.getCenter().y - 180);*/

		window.draw(text);
		window.draw(health_text);
		//window.draw(*player1.animatedSprite);
		window.draw(player1.sprite);
		for (it = entities.begin(); it != entities.end(); it++)
		{
			window.draw((*it)->sprite);
		}
		//window.draw(enemy1.sprite);
		if (!showMissionText) 
		{
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//������� ���� ��� �����	
			window.draw(s_quest); window.draw(text); 
		}
		window.display();
		
	}

	return 0;
}