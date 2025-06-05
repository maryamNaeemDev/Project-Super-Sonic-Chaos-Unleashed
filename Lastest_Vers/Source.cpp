#include <iostream>
#include <fstream>
#include <cstdlib> //for rand func
#include <ctime> //for srand func
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"enemies.h"
#include"../SuperSonic/character.h"
#include"../SuperSonic/collectables.h"
#include"../SuperSonic/Highscore.h"
#include<../SuperSonic/menu.h>
#include"Level.h"
using namespace sf;
using namespace std;

int screen_x = 1200;
int screen_y = 900;

// prototypes 






int main()
{

	RenderWindow window(VideoMode(screen_x, screen_y), "Sonic the Hedgehog-OOP", Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	/////////////////////////////////////////////////////////////////
	// a cell is 64 by 64 pixels

	// 's' is regular space
	// 'q' is wall1 or floor1
	// 'w' is wall2 or floor2
	// 'e' is wall3 or floor3
	// 'b' is breakable wall
	// 'z' is spring
	// 'p' is for spike
	//now for decor
	//  'l' is for leaf brick
	// b is for breakable wall
	// o is for lion
	// // u is power up
	// Uppercase for not interactable background accessories

	// C is for crystals

	const int cell_size = 64;
	const int height = 14;
	const int width = 200;



	Music lvlMus;

	lvlMus.openFromFile("Data/labrynth.ogg");
	lvlMus.setVolume(0);
	lvlMus.play();
	lvlMus.setLoop(true);

	//Textures and sprites loading






	///////////////////////////////////////
	//eneimies declaration
	//start x,starty, end x and end y
	//MottoBug mottobug(64 * 69, 64 * 9.8, 64 * 86, 64 * 9.8);
	//mottobug.setScale(3.0f, 3.0f);
	//mottobug.loadSprite("Data/Enemies/mottobug1.png"); // Path to your MottoBug sprite

	////////////////////////////////////////////////////////
	float player_x = 100;
	float player_y = 100;

	float max_speed = 15;

	float velocityX = 0;
	float velocityY = 0;

	float jumpStrength = -20; // Initial jump velocity
	float gravity = 1;  // Gravity acceleration



	//SPrites for sonic!!


	float scale_x = 2.5;
	float scale_y = 2.5;





	bool toggle[10] = { 0 };
	int i = 0;

	bool boggle[8] = { 0 };
	int j = 0;





	float offset_x = 0;
	float offset_y = 0;

	float terminal_Velocity = 20;

	float acceleration = 0.2;


	View view(FloatRect(0, 0, 1200, 900));
	FloatRect cameraview(0, 0, 400 + 90 + 90 + 5, 200 + 50 + 50 + 10);

	////////////////////////////
	int raw_img_x = 24;
	int raw_img_y = 35;

	int Pheight = raw_img_y * scale_y;
	int Pwidth = raw_img_x * scale_x;

	//only to adjust the player's hitbox

	int hit_box_factor_x = 8 * scale_x;
	int hit_box_factor_y = 5 * scale_y;

	int score = 0;

	bool t;
	bool s = true;
	bool k;



	////////////////////////////////////////////////////////
	sf::RectangleShape cameraBox;
	cameraBox.setSize(sf::Vector2f(cameraview.width, 900 - cameraview.height));
	cameraBox.setFillColor(sf::Color(0, 255, 0, 50));  // Semi-transparent green
	cameraBox.setOutlineColor(sf::Color::Green);
	cameraBox.setOutlineThickness(2);


	Font font;
	if (!font.loadFromFile("Data/DungeonFont.ttf")) {
		return EXIT_FAILURE;
	}
	Event ev;
	Highscore highscore(font);
	Menu menu(font);

	int selected = menu.run(window);
	if (selected == 1 || selected==0) // "Levels" selected from main menu
	{
		int levelChoice;
		int actualLevel;
		if (selected == 1)
		{
			levelChoice = menu.runLevelMenu(window);
		}
		else
		{
			levelChoice = 10;
		}
		if (levelChoice >= 10) // A level was selected
		{
			actualLevel = levelChoice - 10;
			// Start the selected level (actualLevel will be 0-3)
			switch (actualLevel)
			{
			case 0:
			{
				highscore.getPlayerName(window);
				Sonic* sonic;
				sonic = new Sonic;
				Player* player = new Player(sonic);
				Knuckles* knuckles;
				knuckles = new Knuckles;
				Computer_Controlled c1(knuckles, sonic);
				Tails* tails;
				tails = new Tails;
				Computer_Controlled c2(tails, knuckles);
				Level1 level(screen_x, screen_y);
				level.initialization();
				while (window.isOpen())
				{

					while (window.pollEvent(ev))
					{


						if (ev.type == Event::Closed)
						{
							window.close();
						}

						if (ev.type == Event::KeyPressed)
						{
						}

					}

					if (Keyboard::isKeyPressed(Keyboard::Escape))
					{
						window.close();
					}

					///// PARTTT OF ANIMATIONSSSSS ////////
					if (i > 10)
						i = 0;
					i++;
					for (int j = 0; j < 10; j++)
					{
						if (j == i)
						{
							toggle[j] = true;
						}
						else
							toggle[j] = false;
					}

					if (j > 8)
						j = 0;
					j++;
					for (int k = 0; k < 8; k++)
					{
						if (k == i)
						{
							boggle[k] = true;
						}
						else
							boggle[k] = false;
					}
					if (player->getHp() <= 0)
						break;
					score += player->getScore();

					if (player->getRingsCollected() == level.getRingCount() && (player->getX()/64 > level.getWidth() - (10)))
					{
						break;
					}
					level.runlevel(window, toggle, boggle, player, c1, c2, knuckles, sonic, tails, view, cameraview);
					///// PARTTT OF ANIMATIONSSSSS ////////


				}

				/*cout << "Rings:" << player->getRingsCollected()<<endl;
				cout << "HP: " << player->getHp() << endl;*/
				highscore.savePlayerData(score);
				int hp = player->getHp();
				delete sonic;
				delete knuckles;
				delete tails;
				delete player;
				if (hp <= 0)
					break;
				level.~Level1();
			}
			case 1:
			{
				Sonic* sonic;
				sonic = new Sonic;
				Player* player = new Player(sonic);
				Knuckles* knuckles;
				knuckles = new Knuckles;
				Computer_Controlled c1(knuckles, sonic);
				Tails* tails;
				tails = new Tails;
				Computer_Controlled c2(tails, knuckles);
				Level2 level2(screen_x, screen_y);
				level2.initialization();
				while (window.isOpen())
				{

					while (window.pollEvent(ev))
					{


						if (ev.type == Event::Closed)
						{
							window.close();
						}

						if (ev.type == Event::KeyPressed)
						{
						}

					}

					if (Keyboard::isKeyPressed(Keyboard::Escape))
					{
						window.close();
					}

					///// PARTTT OF ANIMATIONSSSSS ////////
					if (i > 10)
						i = 0;
					i++;
					for (int j = 0; j < 10; j++)
					{
						if (j == i)
						{
							toggle[j] = true;
						}
						else
							toggle[j] = false;
					}

					if (j > 8)
						j = 0;
					j++;
					for (int k = 0; k < 8; k++)
					{
						if (k == i)
						{
							boggle[k] = true;
						}
						else
							boggle[k] = false;
					}
					if (player->getHp() <= 0)
						break;
					score += player->getScore();
					if (player->getRingsCollected() == level2.getRingCount() && (player->getX() > level2.getWidth() * 64 - (64 * 4)))
					{
						break;
					}
					level2.runlevel(window, toggle, boggle, player, c1, c2, knuckles, sonic, tails, view, cameraview);
					///// PARTTT OF ANIMATIONSSSSS ////////


				}
				/*cout << "Rings:" << player->getRingsCollected()<<endl;
				cout << "HP: " << player->getHp() << endl;*/

				highscore.savePlayerData(score);
				int hp = player->getHp();
				delete sonic;
				delete knuckles;
				delete tails;
				delete player;
				if (hp <= 0)
					break;
				level2.~Level2();
			}

			case 2:
			{
				Sonic* sonic;
				sonic = new Sonic;
				Player* player = new Player(sonic);
				Knuckles* knuckles;
				knuckles = new Knuckles;
				Computer_Controlled c1(knuckles, sonic);
				Tails* tails;
				tails = new Tails;
				Computer_Controlled c2(tails, knuckles);
				Level3 level3(screen_x, screen_y);
				level3.initialization();
				while (window.isOpen())
				{

					while (window.pollEvent(ev))
					{


						if (ev.type == Event::Closed)
						{
							window.close();
						}

						if (ev.type == Event::KeyPressed)
						{
						}

					}

					if (Keyboard::isKeyPressed(Keyboard::Escape))
					{
						window.close();
					}

					///// PARTTT OF ANIMATIONSSSSS ////////
					if (i > 10)
						i = 0;
					i++;
					for (int j = 0; j < 10; j++)
					{
						if (j == i)
						{
							toggle[j] = true;
						}
						else
							toggle[j] = false;
					}

					if (j > 8)
						j = 0;
					j++;
					for (int k = 0; k < 8; k++)
					{
						if (k == i)
						{
							boggle[k] = true;
						}
						else
							boggle[k] = false;
					}
					if (player->getHp() <= 0)
						break;
					score += player->getScore();
					if (player->getRingsCollected() == level3.getRingCount() && (player->getX()>level3.getWidth()*64-(64*4)))
					{
						break;
					}
					level3.runlevel(window, toggle, boggle, player, c1, c2, knuckles, sonic, tails, view, cameraview);
					///// PARTTT OF ANIMATIONSSSSS ////////


				}

				/*cout << "Rings:" << player->getRingsCollected()<<endl;
				cout << "HP: " << player->getHp() << endl;*/

				highscore.savePlayerData(score);
				int hp = player->getHp();
				delete sonic;
				delete knuckles;
				delete tails;
				delete player;
				if (hp <= 0)
					break;
				level3.~Level3();
			}
			case 3:
			{
				Sonic* sonic;
				sonic = new Sonic;
				Player* player = new Player(sonic);
				Knuckles* knuckles;
				knuckles = new Knuckles;
				Computer_Controlled c1(knuckles, sonic);
				Tails* tails;
				tails = new Tails;
				Computer_Controlled c2(tails, knuckles);
				Level4 level4(screen_x, screen_y);
				level4.initialization();
				while (window.isOpen())
				{

					while (window.pollEvent(ev))
					{


						if (ev.type == Event::Closed)
						{
							window.close();
						}

						if (ev.type == Event::KeyPressed)
						{
						}

					}

					if (Keyboard::isKeyPressed(Keyboard::Escape))
					{
						window.close();
					}

					///// PARTTT OF ANIMATIONSSSSS ////////
					if (i > 10)
						i = 0;
					i++;
					for (int j = 0; j < 10; j++)
					{
						if (j == i)
						{
							toggle[j] = true;
						}
						else
							toggle[j] = false;
					}

					if (j > 8)
						j = 0;
					j++;
					for (int k = 0; k < 8; k++)
					{
						if (k == i)
						{
							boggle[k] = true;
						}
						else
							boggle[k] = false;
					}
					if (player->getHp() <= 0)
						break;
					score += player->getScore();
					/*if ()
					{
						break;
					}*/
					level4.runlevel(window, toggle, boggle, player, c1, c2, knuckles, sonic, tails, view, cameraview);
					///// PARTTT OF ANIMATIONSSSSS ////////


				}
				/*cout << "Rings:" << player->getRingsCollected()<<endl;
				cout << "HP: " << player->getHp() << endl;*/
				highscore.savePlayerData(score);
				int hp = player->getHp();
				delete sonic;
				delete knuckles;
				delete tails;
				delete player;
				if (hp <= 0)
					break;
				level4.~Level4();
			}
			highscore.getHighScores();
			highscore.displayHighScores(window);

			}
		}
	}
	else if (selected == 3)
	{
		string highScoreNames[3];
		int highScores[3];
		highscore.getHighScores();
		highscore.displayHighScores(window);
	}
	return 0;
}
	

