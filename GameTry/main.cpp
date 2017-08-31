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

#include "map.h"
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

	sf::Image platform_image;
	platform_image.loadFromFile("images/DungeonCrawlTileset.png");

	Object player = level.GetObject("player");
	Object enemy = level.GetObject("enemy");
	Object platform = level.GetObject("MovingPlatform");

	std::list <Entity*> entities;
	std::list <Entity*>::iterator it;//�������� ��� ������
	std::list <Entity*>::iterator it2;//������ ��������

	std::vector<Object> e;//������ ��� �������� ������, �������� � �������

	e = level.GetObjects("enemy");//��� ������� ����� �� tmx ����� �������� � ���� �������
	e = level.GetObjects("MovingPlatform");//��� ��������� ����

	Player player1(hero_image, "Player1", level, player.rect.left, player.rect.top, 40, 30);
	//Enemy enemy1(hero_image, "EasyEnemy", level, enemy.rect.left, enemy.rect.top, 40, 30);
	for (int i = 0; i < e.size(); i++)
	{
		entities.push_back(new Enemy(hero_image, "EasyEnemy", level, e[i].rect.left, e[i].rect.top, 40, 30));
		entities.push_back(new MovingPlatform(platform_image, "SimplePlatform", level, e[i].rect.left, e[i].rect.top, 32*4, 32));
	}

	sf::Image map_image;
	map_image.loadFromFile("images/map.png");
	sf::Texture map_texture;
	map_texture.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map_texture);

	sf::Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(sf::Color(0, 0, 0));
	sf::Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	sf::Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(sf::IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.6f, 0.6f);//���� ��������� ��������, => ������ ���� ������

	RandomMapGenerate(5);

	while (window.isOpen())
	{
		
		float time = clock.getElapsedTime().asMicroseconds();
		if (player1.isLive) timeOfGame= gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 800;

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//�������� ����� �������
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		//std::cout << pixelPos.x << "\n";//������� �� ���������� � ������� ������� � ������� (��� �� ����� ������ ������ ����)
		//std::cout << pos.x << "\n";//������� �� �,������� ��������������� � ������� ����������

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			//player1.MouseControl(event, pos);
			//player1.AutoMove(player1.tempX, player1.tempY, time);

			if (event.type == sf::Event::KeyPressed)//������� ������� �������
				if ((event.key.code == sf::Keyboard::Tab)) //���� ������� ���
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
		}
		if (player1.isLive)
		{
		
			GetPlayerCoordinatesForView(player1.GetPlayerCoordinateX(), player1.GetPlayerCoordinateY());
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);//������� � ������ ���������� ���� ������������ ���� (�,�)
			if (localPosition.x < 3) view.move(time*-0.5, 0);
			else if (localPosition.x > window.getSize().x - 3) view.move(time*0.5, 0);
			else if (localPosition.y < 3) view.move(0, time*-0.5);
			else if (localPosition.y > window.getSize().y - 3) view.move(0, time*0.5);

			
			if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				entities.push_back(new Enemy(hero_image, "EasyEnemy", level, localPosition.x, localPosition.y, 40, 30));
			}
	
		}
		
		player1.Update(time);
		for (it = entities.begin(); it != entities.end(); it++)
		{
			//�������� ���� ������
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				//���� ����� ������
				if ((*it)->GetRect() != (*it2)->GetRect())
				{
					//� ��� �� ������� ������������
					if ((*it)->GetRect().intersects((*it2)->GetRect()) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))
					{
						//����� ������������ ��
						(*it)->dx *= -1;
						(*it)->sprite.scale(-1, 1);
					}
				}
				
			}

			if ((*it)->GetRect().intersects(player1.GetRect()))//���� ������������� ������� ������� ������������ � �������
			{
				if ((*it)->name == "EasyEnemy")
				{
					if ((player1.dy>0 && player1.onGround == false) || (player1.dy>0))
					{
						//���� �������� �� �����,�� ���� ����� �������� 0,����������� �� ���� ���� �����,���� ��� �������� 0
						//��� ���� ��������� � �� ��������
						//(*it)->dx = 0; 
						player1.dy = -0.2; 
						//(*it)->health = 0; 
					}
					if ((*it)->dx > 0)
					{
						//���� ���� ���� ������ ����� ����������� ��� � �������������
						(*it)->x = player1.x - (*it)->w;
						(*it)->dx *= -1;
						(*it)->sprite.scale(-1, 1);
						(*it)->dy = -0.3;
					}
					else if ((*it)->dx < 0)
					{
						//���� ���� ���� ����� ����� ����������� ��� � �������������
						(*it)->x = player1.x + (*it)->w;
						(*it)->dx *= -1;
						(*it)->sprite.scale(-1, 1);
						(*it)->dy = -0.3;
					}
					else
					{
						player1.health -= 5;	//����� ���� ������� � ��� ����� � ����� ����
					}
				}
				if ((*it)->name == "SimplePlatform")
				{
					if (player1.dy > 0 && player1.onGround == false)
					{
						player1.onGround = true;
						player1.x = (*it)->x;
						player1.y = (*it)->y;
					}
				}
			}
		}
		for (it = entities.begin(); it != entities.end();)//������� ��� ���������� �� ������ �� �����
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
		
		//enemy1.Update(time);
		MoveViewMap(time);
		ChangeViewMap(time);
		window.setView(view);
		window.clear(sf::Color(128, 106, 89));
		//������ ���������
		/*for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (TileMap[i][j] == ' ') s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
				else if (TileMap[i][j] == '0') s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
				else if (TileMap[i][j] == 's') s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
				else if (TileMap[i][j] == 'f') s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
				else if (TileMap[i][j] == 'h') s_map.setTextureRect(sf::IntRect(128, 0, 32, 32));
				else if (TileMap[i][j] == 'g') s_map.setTextureRect(sf::IntRect(161, 0, 32, 32));
				s_map.setPosition(j*32, i*32);
				window.draw(s_map);
			}
		}*/
		//�����
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
		window.draw(s_map);
		window.display();
		
	}

	return 0;
}