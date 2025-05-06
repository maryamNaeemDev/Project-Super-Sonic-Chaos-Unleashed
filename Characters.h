#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib> //for rand func
#include <ctime> //for srand func
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"enemies.h"
using namespace std;
using namespace sf;








class Characters
{
protected:
	int** Active;
	int hp;
	int hits;

	float player_x = 100;
	float player_y = 100;
	float velocityY = 0;


	float posx = player_x;
	float posy = player_y;

	bool onGround = false;
	float jumpStrength = -20;

	int s_position_x, s_position_y;
	int f_position_x, f_position_y;
	int flytime=6;

	bool switche, twitche;
	bool bruh;
	bool truh;
	bool punch = 0;
	bool isjumping=0;
	bool fly = 0;

	Texture LstillTex;
	Sprite LstillSprite;
	Texture RstillTex;
	Sprite RstillSprite;


	Sprite leftjog;
	Texture leftjog1;
	Texture leftjog2;
	Texture leftjog3;
	Texture leftjog4;
	Texture leftjog5;
	Texture leftjog6;
	Texture leftjog7;
	Texture leftjog8;
	Texture leftjog9;
	Texture leftjog10;

	Sprite rightjog;
	Texture rightjog1;
	Texture rightjog2;
	Texture rightjog3;
	Texture rightjog4;
	Texture rightjog5;
	Texture rightjog6;
	Texture rightjog7;
	Texture rightjog8;
	Texture rightjog9;
	Texture rightjog10;

	Sprite leftup;
	Texture leftup1;
	Texture leftup2;
	Texture leftup3;
	Texture leftup4;
	Texture leftup5;
	Texture leftup6;
	Texture leftup7;
	Texture leftup8;

	Sprite rightup;
	Texture rightup1;
	Texture rightup2;
	Texture rightup3;
	Texture rightup4;
	Texture rightup5;
	Texture rightup6;
	Texture rightup7;
	Texture rightup8;

	Sprite punchin;
	Texture punchin1;
	Texture punchin2;
	Texture punchin3;
	Texture punchin4;
	Texture punchin5;
	Texture punchin6;
	Texture punchin7;
	Texture punchin8;

	Sprite bunchin;
	Texture bunchin1;
	Texture bunchin2;
	Texture bunchin3;
	Texture bunchin4;
	Texture bunchin5;
	Texture bunchin6;
	Texture bunchin7;
	Texture bunchin8;

	Sprite rightfly;
	Texture rightfly1;
	Texture rightfly2;
	Texture rightfly3;
	Texture rightfly4;
	Texture rightfly5;
	Texture rightfly6;
	Texture rightfly7;
	Texture rightfly8;

	Sprite leftfly;
	Texture leftfly1;
	Texture leftfly2;
	Texture leftfly3;
	Texture leftfly4;
	Texture leftfly5;
	Texture leftfly6;
	Texture leftfly7;
	Texture leftfly8;

	sf::Vector2f scaleFactor = { 1.0f, 1.0f };
	float scale_x = 2.5;
	float scale_y = 2.5;
public:
	/*virtual void move() = 0;
	virtual void attack() = 0;
	virtual void boost() = 0;*/
	float getX() const { return player_x; }
	void setX(float n) { player_x = n; }
	float getY() const { return player_y; }
	void setY(float n) { player_y = n; }
	bool getFly() { return fly; }
	void setFly(bool b) { fly = b; }
	int getFlyTime() { return flytime; }
	void setFlyTime(int b) { flytime = b; }
	void setIsJumping(bool j) { isjumping = j; }
	bool getIsJumpung() { return isjumping; }
	void setVelocityY(float v) {velocityY=v;}
	void setSwitche(bool swi) { switche = swi; }
	void setTwitche(bool twi) { twitche = twi; }
	void setTruh(bool tr) { truh = tr; }
	bool getTruh() { return truh; }
	void setBruh(bool br) { bruh = br; }
	bool getBruh() { return bruh; }
	bool getPunch() { return punch; }
	void setPunch(bool pun) { punch = pun; }
	bool getOnGround() const { return onGround; }
	float getJumpStrength() const { return jumpStrength; }
	void setPosition(float x, float y) { player_x = x; player_y = y; }
	
	void player_gravity(char** lvl, float& offset_y, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, const int cell_size, int& Pheight, int& Pwidth)
	{
		int gridX = static_cast<int>(player_x) / cell_size;
		int gridY = static_cast<int>(player_y) / cell_size;

		offset_y = player_y;
		offset_y += velocityY;

		char bottom_left = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];
		char bottom_right = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth - hit_box_factor_x) / cell_size];
		char bottom_center = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth / 2) / cell_size];

		int groundPoints = 0;

		if (bottom_left == 'w' || bottom_left == 'q') groundPoints++;
		if (bottom_right == 'w' || bottom_right == 'q') groundPoints++;
		if (bottom_center == 'w' || bottom_center == 'q') groundPoints++;

		if (velocityY >= 0)
		{
			if (groundPoints >= 2)
			{
				int blockTopY = ((int)(offset_y + Pheight) / cell_size) * cell_size;
				player_y = blockTopY - Pheight;
				onGround = true;
			}
			else
			{
				player_y = offset_y;
				onGround = false;
			}
		}
		else  
		{
			player_y = offset_y;
			onGround = false;
		}

		if (!onGround)
		{
			velocityY += gravity;
			if (velocityY >= terminal_Velocity) velocityY = terminal_Velocity;
		}
		else
		{
			velocityY = 0;
		}

	}
	void animation(bool toggle[], bool boggle[])
	{

		Vector2f currentPos = leftjog.getPosition();
		if (switche == true)
		{
			if (toggle[0] == true)
			{
				leftjog.setTexture(leftjog1);
				leftjog.setScale(scale_x, scale_y);
			}
			else if (toggle[1] == true)
			{
				leftjog.setTexture(leftjog2);
				leftjog.setScale(scale_x, scale_y);
			}
			else if (toggle[2] == true)
			{
				leftjog.setTexture(leftjog3);
				leftjog.setScale(scale_x, scale_y);
			}
			else if (toggle[3] == true)
			{
				leftjog.setTexture(leftjog4);
				leftjog.setScale(scale_x, scale_y);
			}
			else if (toggle[4] == true)
			{
				leftjog.setTexture(leftjog5);
				leftjog.setScale(scale_x, scale_y);
			}
			else if (toggle[5] == true)
			{
				leftjog.setTexture(leftjog6);
				leftjog.setScale(scale_x, scale_y);
			}
			else if (toggle[6] == true)
			{
				leftjog.setTexture(leftjog7);
				leftjog.setScale(scale_x, scale_y);
			}
			else if (toggle[7] == true)
			{
				leftjog.setTexture(leftjog8);
				leftjog.setScale(scale_x, scale_y);
			}
			else if (toggle[8] == true)
			{
				leftjog.setTexture(leftjog9);
				leftjog.setScale(scale_x, scale_y);
			}
			else if (toggle[9] == true)
			{
				leftjog.setTexture(leftjog10);
				leftjog.setScale(scale_x, scale_y);
			}
			leftjog.setPosition(currentPos);
		}

		else if (twitche == true)
		{
			Vector2f currentPos1 = rightjog.getPosition();
			if (toggle[0] == true)
			{
				rightjog.setTexture(rightjog1);
				rightjog.setScale(scale_x, scale_y);
			}
			else if (toggle[1] == true)
			{
				rightjog.setTexture(rightjog2);
				rightjog.setScale(scale_x, scale_y);
			}
			else if (toggle[2] == true)
			{
				rightjog.setTexture(rightjog3);
				rightjog.setScale(scale_x, scale_y);
			}
			else if (toggle[3] == true)
			{
				rightjog.setTexture(rightjog4);
				rightjog.setScale(scale_x, scale_y);
			}
			else if (toggle[4] == true)
			{
				rightjog.setTexture(rightjog5);
				rightjog.setScale(scale_x, scale_y);
			}
			else if (toggle[5] == true)
			{
				rightjog.setTexture(rightjog6);
				rightjog.setScale(scale_x, scale_y);
			}
			else if (toggle[6] == true)
			{
				rightjog.setTexture(rightjog7);
				rightjog.setScale(scale_x, scale_y);
			}
			else if (toggle[7] == true)
			{
				rightjog.setTexture(rightjog8);
				rightjog.setScale(scale_x, scale_y);
			}
			else if (toggle[8] == true)
			{
				rightjog.setTexture(rightjog9);
				rightjog.setScale(scale_x, scale_y);
			}
			else if (toggle[9] == true)
			{
				rightjog.setTexture(rightjog10);
				rightjog.setScale(scale_x, scale_y);
			}
			rightjog.setPosition(currentPos1);
		}
		else
		{

		}
		if (bruh)
		{
			Vector2f currentPos = leftup.getPosition();
			if (boggle[0])
			{
				leftup.setTexture(leftup1);
				leftup.setScale(scale_x, scale_y);
			}
			else if (boggle[1])
			{
				leftup.setTexture(leftup2);
				leftup.setScale(scale_x, scale_y);
			}
			else if (boggle[2])
			{
				leftup.setTexture(leftup3);
				leftup.setScale(scale_x, scale_y);
			}
			else if (boggle[3])
			{
				leftup.setTexture(leftup4);
				leftup.setScale(scale_x, scale_y);
			}
			else if (boggle[4])
			{
				leftup.setTexture(leftup5);
				leftup.setScale(scale_x, scale_y);
			}
			else if (boggle[5])
			{
				leftup.setTexture(leftup6);
				leftup.setScale(scale_x, scale_y);
			}
			else if (boggle[6])
			{
				leftup.setTexture(leftup7);
				leftup.setScale(scale_x, scale_y);
			}
			else if (boggle[7])
			{
				leftup.setTexture(leftup8);
				leftup.setScale(scale_x, scale_y);
			}
			leftup.setPosition(currentPos);

			Vector2f currentPos1 = bunchin.getPosition();
			if (boggle[0])
			{
				bunchin.setTexture(bunchin1);
				bunchin.setScale(scale_x, scale_y);
			}
			else if (boggle[1])
			{
				bunchin.setTexture(bunchin2);
				bunchin.setScale(scale_x, scale_y);
			}
			else if (boggle[2])
			{
				bunchin.setTexture(bunchin3);
				bunchin.setScale(scale_x, scale_y);
			}
			else if (boggle[3])
			{
				bunchin.setTexture(bunchin4);
				bunchin.setScale(scale_x, scale_y);
			}
			else if (boggle[4])
			{
				bunchin.setTexture(bunchin5);
				bunchin.setScale(scale_x, scale_y);
			}
			else if (boggle[5])
			{
				bunchin.setTexture(bunchin6);
				bunchin.setScale(scale_x, scale_y);
			}
			else if (boggle[6])
			{
				bunchin.setTexture(bunchin7);
				bunchin.setScale(scale_x, scale_y);
			}
			else if (boggle[7])
			{
				bunchin.setTexture(bunchin8);
				bunchin.setScale(scale_x, scale_y);
			}
			bunchin.setPosition(currentPos1);

			Vector2f currentPos2 = leftfly.getPosition();
			if (boggle[0])
			{
				leftfly.setTexture(leftfly1);
				leftfly.setScale(scale_x, scale_y);
			}
			else if (boggle[1])
			{
				leftfly.setTexture(leftfly2);
				leftfly.setScale(scale_x, scale_y);
			}
			else if (boggle[2])
			{
				leftfly.setTexture(leftfly3);
				leftfly.setScale(scale_x, scale_y);
			}
			else if (boggle[3])
			{
				leftfly.setTexture(leftfly4);
				leftfly.setScale(scale_x, scale_y);
			}
			else if (boggle[4])
			{
				leftfly.setTexture(leftfly5);
				leftfly.setScale(scale_x, scale_y);
			}
			else if (boggle[5])
			{
				leftfly.setTexture(leftfly6);
				leftfly.setScale(scale_x, scale_y);
			}
			else if (boggle[6])
			{
				leftfly.setTexture(leftfly7);
				leftfly.setScale(scale_x, scale_y);
			}
			else if (boggle[7])
			{
				leftfly.setTexture(leftfly8);
				leftfly.setScale(scale_x, scale_y);
			}
			leftfly.setPosition(currentPos2);
		}
		else
		{
			Vector2f currentPos = rightup.getPosition();
			if (boggle[0])
			{
				rightup.setTexture(rightup1);
				rightup.setScale(scale_x, scale_y);
			}
			else if (boggle[1])
			{
				rightup.setTexture(rightup2);
				rightup.setScale(scale_x, scale_y);
			}
			else if (boggle[2])
			{
				rightup.setTexture(rightup3);
				rightup.setScale(scale_x, scale_y);
			}
			else if (boggle[3])
			{
				rightup.setTexture(rightup4);
				rightup.setScale(scale_x, scale_y);
			}
			else if (boggle[4])
			{
				rightup.setTexture(rightup5);
				rightup.setScale(scale_x, scale_y);
			}
			else if (boggle[5])
			{
				rightup.setTexture(rightup6);
				rightup.setScale(scale_x, scale_y);
			}
			else if (boggle[6])
			{
				rightup.setTexture(rightup7);
				rightup.setScale(scale_x, scale_y);
			}
			else if (boggle[7])
			{
				rightup.setTexture(rightup8);
				rightup.setScale(scale_x, scale_y);
			}
			rightup.setPosition(currentPos);

				Vector2f currentPos1 = punchin.getPosition();
				if (boggle[0])
				{
					punchin.setTexture(punchin1);
					punchin.setScale(scale_x, scale_y);
				}
				else if (boggle[1])
				{
					punchin.setTexture(punchin2);
					punchin.setScale(scale_x, scale_y);
				}
				else if (boggle[2])
				{
					punchin.setTexture(punchin3);
					punchin.setScale(scale_x, scale_y);
				}
				else if (boggle[3])
				{
					punchin.setTexture(punchin4);
					punchin.setScale(scale_x, scale_y);
				}
				else if (boggle[4])
				{
					punchin.setTexture(punchin5);
					punchin.setScale(scale_x, scale_y);
				}
				else if (boggle[5])
				{
					punchin.setTexture(punchin6);
					punchin.setScale(scale_x, scale_y);
				}
				else if (boggle[6])
				{
					punchin.setTexture(punchin7);
					punchin.setScale(scale_x, scale_y);
				}
				else if (boggle[7])
				{
					punchin.setTexture(punchin8);
					punchin.setScale(scale_x, scale_y);
				}
				punchin.setPosition(currentPos1);

				Vector2f currentPos2 = rightfly.getPosition();
				if (boggle[0])
				{
					rightfly.setTexture(rightfly1);
					rightfly.setScale(scale_x, scale_y);
				}
				else if (boggle[1])
				{
					rightfly.setTexture(rightfly2);
					rightfly.setScale(scale_x, scale_y);
				}
				else if (boggle[2])
				{
					rightfly.setTexture(rightfly3);
					rightfly.setScale(scale_x, scale_y);
				}
				else if (boggle[3])
				{
					rightfly.setTexture(rightfly4);
					rightfly.setScale(scale_x, scale_y);
				}
				else if (boggle[4])
				{
					rightfly.setTexture(rightfly5);
					rightfly.setScale(scale_x, scale_y);
				}
				else if (boggle[5])
				{
					rightfly.setTexture(rightfly6);
					rightfly.setScale(scale_x, scale_y);
				}
				else if (boggle[6])
				{
					rightfly.setTexture(rightfly7);
					rightfly.setScale(scale_x, scale_y);
				}
				else if (boggle[7])
				{
					rightfly.setTexture(rightfly8);
					rightfly.setScale(scale_x, scale_y);
				}
				rightfly.setPosition(currentPos2);
		}

	}
	virtual void draw_player(RenderWindow& window)
	{
		if (switche) {
			if (truh) {
				leftup.setPosition(player_x, player_y);
				window.draw(leftup);
			}
			else {
				leftjog.setPosition(player_x, player_y-10);
				window.draw(leftjog);
			}
		}
		else if (twitche) {
			if (truh) {
				rightup.setPosition(player_x, player_y);
				window.draw(rightup);
			}
			else {
				rightjog.setPosition(player_x, player_y-10);
				window.draw(rightjog);
			}
		}
		else {
			if (bruh) {
				if (truh) {
					leftup.setPosition(player_x, player_y);
					window.draw(leftup);
				}
				else if (punch)
				{
					bunchin.setPosition(player_x, player_y-13);
					window.draw(bunchin);
				}
				else if (fly)
				{
					leftfly.setPosition(player_x, player_y);
					window.draw(leftfly);
				}
				else {
					LstillSprite.setPosition(player_x, player_y-13);
					window.draw(LstillSprite);
				}
				
			}
			else {
				if (truh) {
					rightup.setPosition(player_x, player_y);
					window.draw(rightup);
				}
				else if (punch)
				{
					punchin.setPosition(player_x, player_y-13);
					window.draw(punchin);
				}
				else if (fly)
				{
					rightfly.setPosition(player_x, player_y);
					window.draw(rightfly);
				}
				else {
					RstillSprite.setPosition(player_x, player_y-13);
					window.draw(RstillSprite);
				}
			}
		}


	}
	void move_right(char** lvl, const int cell_size, const int width)
	{
		Keyboard key;
		int gridX = static_cast<int>(player_x) / cell_size;
		int gridY = static_cast<int>(player_y) / cell_size;
		if (gridX < width - 1 && lvl[gridY+1][gridX+2] != 'w')
		{
			player_x += 8;
			if (!onGround && key.isKeyPressed(key.Space))
				truh = true;
			else
			{
				truh = false;
				twitche = true;
				switche = false;
			}
		}
		bruh = false;
	}
	void move_left(char** lvl, const int cell_size, const int width)
	{
		Keyboard key;
		int gridX = static_cast<int>(player_x) / cell_size;
		int gridY = static_cast<int>(player_y) / cell_size;
		if (gridX > 0 && lvl[gridY+1][gridX] != 'w')
		{
			player_x -= 8;
			if (!onGround && key.isKeyPressed(key.Space))
				truh = true;
			else
			{
				truh = false;
				twitche = false;
				switche = true;
			}
		}
		bruh = true;
	}
	void jumping(Clock& delayjump, char** lvl, const int cell_size)
	{
			int gridX = static_cast<int>(player_x) / cell_size;
			int gridY = static_cast<int>(player_y) / cell_size;
			/*if (lvl[gridY - 4][gridX] != 'w'&& lvl[gridY - 6][gridX] != 'w'&&lvl[gridY - 7][gridX] != 'w')*/
			{
				truh = true;
				velocityY = +jumpStrength;
				delayjump.restart();
			}
	}
	
};
class Sonic :public Characters
{

	int hp;
	int hits = 0;

	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;

	bool movingRight = true;
	float speed = 8.0f;
public:
	Sonic()
	{
		LstillTex.loadFromFile("Data/sonic/0left_still.png");
		LstillSprite.setTexture(LstillTex);
		LstillSprite.setScale(scale_x, scale_y);

		RstillTex.loadFromFile("Data/sonic/0right_still.png");
		RstillSprite.setTexture(RstillTex);
		RstillSprite.setScale(scale_x, scale_y);

		bool switche, twitche;
		leftjog1.loadFromFile("Data/sonic/leftjog1.png");
		leftjog2.loadFromFile("Data/sonic/leftjog1.png");
		leftjog3.loadFromFile("Data/sonic/leftjog2.png");
		leftjog4.loadFromFile("Data/sonic/leftjog2.png");
		leftjog5.loadFromFile("Data/sonic/leftjog3.png");
		leftjog6.loadFromFile("Data/sonic/leftjog3.png");
		leftjog7.loadFromFile("Data/sonic/leftjog4.png");
		leftjog8.loadFromFile("Data/sonic/leftjog4.png");
		leftjog9.loadFromFile("Data/sonic/leftjog5.png");
		leftjog10.loadFromFile("Data/sonic/leftjog5.png");

		rightjog1.loadFromFile("Data/sonic/rightjog1.png");
		rightjog2.loadFromFile("Data/sonic/rightjog1.png");
		rightjog3.loadFromFile("Data/sonic/rightjog2.png");
		rightjog4.loadFromFile("Data/sonic/rightjog2.png");
		rightjog5.loadFromFile("Data/sonic/rightjog3.png");
		rightjog6.loadFromFile("Data/sonic/rightjog3.png");
		rightjog7.loadFromFile("Data/sonic/rightjog4.png");
		rightjog8.loadFromFile("Data/sonic/rightjog4.png");
		rightjog9.loadFromFile("Data/sonic/rightjog5.png");
		rightjog10.loadFromFile("Data/sonic/rightjog5.png");

		leftup1.loadFromFile("Data/sonic/leftup1.png");
		leftup2.loadFromFile("Data/sonic/leftup2.png");
		leftup3.loadFromFile("Data/sonic/leftup3.png");
		leftup4.loadFromFile("Data/sonic/leftup4.png");
		leftup5.loadFromFile("Data/sonic/leftup5.png");
		leftup6.loadFromFile("Data/sonic/leftup6.png");
		leftup7.loadFromFile("Data/sonic/leftup7.png");
		leftup8.loadFromFile("Data/sonic/leftup8.png");

		rightup1.loadFromFile("Data/sonic/rightup1.png");
		rightup2.loadFromFile("Data/sonic/rightup2.png");
		rightup3.loadFromFile("Data/sonic/rightup3.png");
		rightup4.loadFromFile("Data/sonic/rightup4.png");
		rightup5.loadFromFile("Data/sonic/rightup5.png");
		rightup6.loadFromFile("Data/sonic/rightup6.png");
		rightup7.loadFromFile("Data/sonic/rightup7.png");
		rightup8.loadFromFile("Data/sonic/rightup8.png");
	}
	void speedrun();

};
class Knuckles : public Characters
{
	sf::Texture texture;
	sf::Sprite sprite;

	Sprite punch;
	Texture punch1;
	Texture punch2;
	Texture punch3;
	Clock breakwallclk;

	int hp = 2;
	int hits = 0;
	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;

	bool movingRight = true;
	float speed = 8.0f;
public:
	Knuckles()
	{
		LstillTex.loadFromFile("Data/knuckles/0left_still.png");
		LstillSprite.setTexture(LstillTex);
		LstillSprite.setScale(scale_x, scale_y);

		RstillTex.loadFromFile("Data/knuckles/0right_still.png");
		RstillSprite.setTexture(RstillTex);
		RstillSprite.setScale(scale_x, scale_y);

		leftjog1.loadFromFile("Data/knuckles/leftjog1.png");
		leftjog2.loadFromFile("Data/knuckles/leftjog2.png");
		leftjog3.loadFromFile("Data/knuckles/leftjog3.png");
		leftjog4.loadFromFile("Data/knuckles/leftjog4.png");
		leftjog5.loadFromFile("Data/knuckles/leftjog5.png");
		leftjog6.loadFromFile("Data/knuckles/leftjog6.png");
		leftjog7.loadFromFile("Data/knuckles/leftjog7.png");
		leftjog8.loadFromFile("Data/knuckles/leftjog8.png");
		leftjog9.loadFromFile("Data/knuckles/leftjog9.png");
		leftjog10.loadFromFile("Data/knuckles/leftjog10.png");

		rightjog1.loadFromFile("Data/knuckles/rightjog1.png");
		rightjog2.loadFromFile("Data/knuckles/rightjog2.png");
		rightjog3.loadFromFile("Data/knuckles/rightjog3.png");
		rightjog4.loadFromFile("Data/knuckles/rightjog4.png");
		rightjog5.loadFromFile("Data/knuckles/rightjog5.png");
		rightjog6.loadFromFile("Data/knuckles/rightjog6.png");
		rightjog7.loadFromFile("Data/knuckles/rightjog7.png");
		rightjog8.loadFromFile("Data/knuckles/rightjog8.png");
		rightjog9.loadFromFile("Data/knuckles/rightjog9.png");
		rightjog10.loadFromFile("Data/knuckles/rightjog10.png");

		leftup1.loadFromFile("Data/knuckles/leftup1.png");
		leftup2.loadFromFile("Data/knuckles/leftup2.png");
		leftup3.loadFromFile("Data/knuckles/leftup3.png");
		leftup4.loadFromFile("Data/knuckles/leftup4.png");
		leftup5.loadFromFile("Data/knuckles/leftup5.png");
		leftup6.loadFromFile("Data/knuckles/leftup6.png");
		leftup7.loadFromFile("Data/knuckles/leftup7.png");
		leftup8.loadFromFile("Data/knuckles/leftup8.png");

		rightup1.loadFromFile("Data/knuckles/rightup1.png");
		rightup2.loadFromFile("Data/knuckles/rightup2.png");
		rightup3.loadFromFile("Data/knuckles/rightup3.png");
		rightup4.loadFromFile("Data/knuckles/rightup4.png");
		rightup5.loadFromFile("Data/knuckles/rightup5.png");
		rightup6.loadFromFile("Data/knuckles/rightup6.png");
		rightup7.loadFromFile("Data/knuckles/rightup7.png");
		rightup8.loadFromFile("Data/knuckles/rightup8.png");

		punchin1.loadFromFile("Data/knuckles/punchin1.png");
		punchin2.loadFromFile("Data/knuckles/punchin2.png");
		punchin3.loadFromFile("Data/knuckles/punchin3.png");
		punchin4.loadFromFile("Data/knuckles/punchin4.png");
		punchin5.loadFromFile("Data/knuckles/punchin5.png");
		punchin6.loadFromFile("Data/knuckles/punchin6.png");
		punchin7.loadFromFile("Data/knuckles/punchin7.png");
		punchin8.loadFromFile("Data/knuckles/punchin8.png");

		bunchin1.loadFromFile("Data/knuckles/bunchin1.png");
		bunchin2.loadFromFile("Data/knuckles/bunchin2.png");
		bunchin3.loadFromFile("Data/knuckles/bunchin3.png");
		bunchin4.loadFromFile("Data/knuckles/bunchin4.png");
		bunchin5.loadFromFile("Data/knuckles/bunchin5.png");
		bunchin6.loadFromFile("Data/knuckles/bunchin6.png");
		bunchin7.loadFromFile("Data/knuckles/bunchin7.png");
		bunchin8.loadFromFile("Data/knuckles/bunchin8.png");
	}
	void breakwall(char** lvl, float& offset_y, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, const int cell_size, int& Pheight, int& Pwidth)
	{
		bool breakin = getPunch();
		int gridX = static_cast<int>(player_x) / cell_size;
		int gridY = static_cast<int>(player_y) / cell_size;
		if (Keyboard::isKeyPressed(Keyboard::B))
		{
			cout << "inside!!";
			setPunch(true);
			if (breakwallclk.getElapsedTime().asSeconds() > 2)
			{
				cout << "Doubleinside!!";
				cout << lvl[gridY][gridX + 2] << endl;
				if ((lvl[gridY][gridX ] == 'w' || lvl[gridY+1][gridX] == 'w') && bruh)
				{
					cout << "HERERERERERERE" << endl;
					lvl[gridY][gridX] = 's';
					lvl[gridY+1][gridX] = 's';
					breakwallclk.restart();
				}
				else if ((lvl[gridY][gridX + 2] == 'w' || lvl[gridY+1][gridX + 2] == 'w') && !bruh)
				{
					cout << "HERERERERERERE" << endl;
					lvl[gridY][gridX + 2] = 's';
					lvl[gridY+1][gridX + 2] = 's';
					breakwallclk.restart();
				}
			}
		}
		else
		{
			breakwallclk.restart();
			setPunch(false);
		}
	}


	
};
class Tails : public Characters
{
	sf::Texture texture;
	sf::Sprite sprite;
	int hp = 2;
	int hits = 0;
	Clock flyclk;
	Clock flyCooldown;  // New cooldown clock
	bool canFly = true;
	

	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;

	bool movingRight = true;
	float speed = 8.0f;
public:
	Tails()
	{
		LstillTex.loadFromFile("Data/tails/0left_still.png");
		LstillSprite.setTexture(LstillTex);
		LstillSprite.setScale(scale_x, scale_y);

		RstillTex.loadFromFile("Data/tails/0right_still.png");
		RstillSprite.setTexture(RstillTex);
		RstillSprite.setScale(scale_x, scale_y);

		leftjog1.loadFromFile("Data/tails/leftjog1.png");
		leftjog2.loadFromFile("Data/tails/leftjog1.png");
		leftjog3.loadFromFile("Data/tails/leftjog2.png");
		leftjog4.loadFromFile("Data/tails/leftjog2.png");
		leftjog5.loadFromFile("Data/tails/leftjog3.png");
		leftjog6.loadFromFile("Data/tails/leftjog3.png");
		leftjog7.loadFromFile("Data/tails/leftjog4.png");
		leftjog8.loadFromFile("Data/tails/leftjog4.png");
		leftjog9.loadFromFile("Data/tails/leftjog5.png");
		leftjog10.loadFromFile("Data/tails/leftjog5.png");

		rightjog1.loadFromFile("Data/tails/rightjog1.png");
		rightjog2.loadFromFile("Data/tails/rightjog1.png");
		rightjog3.loadFromFile("Data/tails/rightjog2.png");
		rightjog4.loadFromFile("Data/tails/rightjog2.png");
		rightjog5.loadFromFile("Data/tails/rightjog3.png");
		rightjog6.loadFromFile("Data/tails/rightjog3.png");
		rightjog7.loadFromFile("Data/tails/rightjog4.png");
		rightjog8.loadFromFile("Data/tails/rightjog4.png");
		rightjog9.loadFromFile("Data/tails/rightjog5.png");
		rightjog10.loadFromFile("Data/tails/rightjog5.png");

		leftup1.loadFromFile("Data/tails/leftup1.png");
		leftup2.loadFromFile("Data/tails/leftup2.png");
		leftup3.loadFromFile("Data/tails/leftup3.png");
		leftup4.loadFromFile("Data/tails/leftup4.png");
		leftup5.loadFromFile("Data/tails/leftup5.png");
		leftup6.loadFromFile("Data/tails/leftup6.png");
		leftup7.loadFromFile("Data/tails/leftup7.png");
		leftup8.loadFromFile("Data/tails/leftup8.png");

		rightup1.loadFromFile("Data/tails/rightup1.png");
		rightup2.loadFromFile("Data/tails/rightup2.png");
		rightup3.loadFromFile("Data/tails/rightup3.png");
		rightup4.loadFromFile("Data/tails/rightup4.png");
		rightup5.loadFromFile("Data/tails/rightup5.png");
		rightup6.loadFromFile("Data/tails/rightup6.png");
		rightup7.loadFromFile("Data/tails/rightup7.png");
		rightup8.loadFromFile("Data/tails/rightup8.png");

		rightfly1.loadFromFile("Data/tails/rightfly1.png");
		rightfly2.loadFromFile("Data/tails/rightfly2.png");
		rightfly3.loadFromFile("Data/tails/rightfly3.png");
		rightfly4.loadFromFile("Data/tails/rightfly4.png");
		rightfly5.loadFromFile("Data/tails/rightfly5.png");
		rightfly6.loadFromFile("Data/tails/rightfly6.png");
		rightfly7.loadFromFile("Data/tails/rightfly7.png");
		rightfly8.loadFromFile("Data/tails/rightfly8.png");

		leftfly1.loadFromFile("Data/tails/leftfly1.png");
		leftfly2.loadFromFile("Data/tails/leftfly2.png");
		leftfly3.loadFromFile("Data/tails/leftfly3.png");
		leftfly4.loadFromFile("Data/tails/leftfly4.png");
		leftfly5.loadFromFile("Data/tails/leftfly5.png");
		leftfly6.loadFromFile("Data/tails/leftfly6.png");
		leftfly7.loadFromFile("Data/tails/leftfly7.png");
		leftfly8.loadFromFile("Data/tails/leftfly8.png");
	}
	  
	void draw_player(RenderWindow& window) override
	{
		if (switche && (!getFly())) {
			if (truh) {
				leftup.setPosition(player_x, player_y + 5);
				window.draw(leftup);
			}
			else {
				leftjog.setPosition(player_x, player_y + 5);
				window.draw(leftjog);
			}
		}
		else if (twitche && (!getFly())) {
			if (truh) {
				rightup.setPosition(player_x, player_y + 5);
				window.draw(rightup);
			}
			else {
				rightjog.setPosition(player_x, player_y + 5);
				window.draw(rightjog);
			}
		}
		else {
			if (bruh) {
				if (truh) {
					leftup.setPosition(player_x, player_y + 5);
					window.draw(leftup);
				}
				else if (getFly())
				{
					leftfly.setPosition(player_x, player_y);
					window.draw(leftfly);
				}
				else {
					LstillSprite.setPosition(player_x, player_y + 12);
					window.draw(LstillSprite);
				}
			}
			else {
				if (truh) {
					rightup.setPosition(player_x, player_y + 5);
					window.draw(rightup);
				}
				else if (getFly())
				{
					rightfly.setPosition(player_x, player_y);
					window.draw(rightfly);
				}
				else {
					RstillSprite.setPosition(player_x, player_y + 12);
					window.draw(RstillSprite);
				}
			}
		}
	}

	void fly(char** lvl, const int cell_size)
	{
		int gridX = static_cast<int>(player_x) / cell_size;
		int gridY = static_cast<int>(player_y) / cell_size;

		// Check cooldown first
		if (!canFly && flyCooldown.getElapsedTime().asSeconds() >= 3.0f) {
			canFly = true;  // Cooldown finished
		}

		if (Keyboard::isKeyPressed(Keyboard::B) && canFly)
		{
			cout << "Flying!" << endl;
			if (flyclk.getElapsedTime().asSeconds() < flytime)
			{
				if (lvl[gridY][gridX] != 'w')
				{
					cout << "Flying active!" << endl;
					player_y -= 8;
					setSwitche(false);
					setTwitche(false);
					setFly(true);
				}
			}
			else
			{
				canFly = false;
				flyclk.restart();
				flyCooldown.restart();
				setFly(false);
			}
		}
		else
		{
			flyclk.restart();
			setFly(false);
		}
	}
	bool isFlyingAvailable() const {
		return canFly;
	}
	float getCooldownProgress() const {
		if (canFly) return 1.0f;
		return std::min(1.0f, flyCooldown.getElapsedTime().asSeconds() / 3.0f);
	}
};

class Player
{
	Characters* active;
	float player_x;
	float player_y;
	Clock delayjump;
	int rings_collected = 0;
	int hp=10;
public:
	Player()
	{
		active = nullptr;
	}
	Player(Characters* yoo)
	{
		active = yoo;
		player_x = active->getX();
		player_y = active->getY();
	}
	int getHp() { return hp; }
	void setHp(int n) { hp = n; }
	int getRingsCollected() { return rings_collected; }
	void setRingsCollected(int r) { rings_collected = r; }
	float getX() { return player_x; }
	float getY() { return player_y; }
	void active_character(Characters* yoo)
	{
		active = yoo;
	}
	void move(char** lvl, const int cell_size, const int width)
	{
		int gridX = static_cast<int>(player_x) / cell_size;
		int gridY = static_cast<int>(player_y) / cell_size;
		if (!active) return;
		Keyboard key;
		if (key.isKeyPressed(key.Left))
		{
			active->move_left(lvl, cell_size, width);
		}
		else if (key.isKeyPressed(key.Right))
		{
			active->move_right(lvl, cell_size, width);
		}
		else
		{
			active->setTwitche(false);
			active->setSwitche(false);
		}
		if (key.isKeyPressed(key.Space) && delayjump.getElapsedTime().asSeconds() > 0.3 && active->getOnGround() )
		{
			
			{
				active->jumping(delayjump, lvl, cell_size);
				active->setIsJumping(true);
			}
		}

		if (!key.isKeyPressed(key.Space))
			active->setTruh(false);
		player_x = active->getX();
		player_y = active->getY();
	}
	void draw(RenderWindow& window)
	{
		if (active)
			active->draw_player(window);
	}
	void animate(bool toggle[], bool boggle[])
	{
		if (active)
			active->animation(toggle, boggle);
	}
	void apply_gravity(char** lvl, float& offset_y, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, const int cell_size, int& Pheight, int& Pwidth)
	{
		if (active)
		{
			if (!(active->getFly()))
				active->player_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		}
	}
};

class Computer_Controlled
{
	Characters* c1;
	Characters* target;
	float followDistance = 200.0f;
	float jumpTriggerHeight = 100.0f;
	//float followSpeed;
	Clock c1Clock;
	Clock jumpCooldown;
	bool active;
	bool isFollowing = false;
	float lastTargetY;

public:
	Computer_Controlled(Characters* a, Characters* b)
	{
		active = true;
		c1 = a;
		target = b;
		lastTargetY = target->getY();
	}

	void computercontrol(Characters* a, Characters* b)
	{
		active = true;
		c1 = a;
		target = b;
		lastTargetY = target->getY();
	}
	void update(char** lvl, const int cell_size, const int width, const int height)
	{
		if (!active) return;

		float targetX = target->getX();
		float targetY = target->getY();
		float currentX = c1->getX();
		float currentY = c1->getY();

		// Calculate if target is moving upward
		bool targetJumping = (targetY < lastTargetY);
		lastTargetY = targetY;

		float directionX = targetX - currentX;
		float directionY = targetY - currentY;
		float distance = sqrt(directionX * directionX + directionY * directionY);

		int checkAhead = directionX > 0 ? 2 : -2;
		int gridX = static_cast<int>(currentX) / cell_size + checkAhead;
		int gridY = static_cast<int>(currentY) / cell_size;

		// Only start following if player gets too far
		if (distance > followDistance) {
			isFollowing = true;
		}
		else if (distance < followDistance - 50.0f) {  // Add some hysteresis
			isFollowing = false;
		}

		if (isFollowing) {
			// Normalize direction if needed
			if (distance > 0) {
				directionX /= distance;
				directionY /= distance;
			}

			// Horizontal movement
			if (directionX > 0.1f) {  // Right
				c1->move_right(lvl, cell_size, width);
				c1->setTwitche(true);
				c1->setSwitche(false);
			}
			else if (directionX < -0.1f) {  // Left
				c1->move_left(lvl, cell_size, width);
				c1->setTwitche(false);
				c1->setSwitche(true);
			}
			else {
				c1->setTwitche(false);
				c1->setSwitche(false);
			}

			bool shouldJump = false;

			if ((targetY < currentY - jumpTriggerHeight) && c1->getOnGround()) {
				shouldJump = true;
			}
			else if (targetJumping && !c1->getTruh() && c1->getOnGround()) {
				shouldJump = true;
			}
			else {

				if (gridX >= 0 && gridX < width && lvl[gridY][gridX] == 'w') {
					shouldJump = true;
				}
			}

			if (shouldJump && jumpCooldown.getElapsedTime().asSeconds() > 0.5f) {
				c1->jumping(c1Clock, lvl, cell_size);
				jumpCooldown.restart();
			}
		}
		else {
			c1->setTwitche(false);
			c1->setSwitche(false);
			c1->setTruh(false);
		}

		if (distance>500 && gridY<height-1 && gridY>1)
		{
			c1->setX(target->getX());
			c1->setY(target->getY());
		}

		if (!(gridY < height - 1 && gridY>1))
		{
			c1->setY(7 * 64);
		}
	}

	void draw(RenderWindow& window)
	{
		if (active)
			c1->draw_player(window);
	}
	void animate(bool toggle[], bool boggle[])
	{
		if (active)
			c1->animation(toggle, boggle);
	}
	void apply_gravity(char** lvl, float& offset_y, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, const int cell_size, int& Pheight, int& Pwidth)
	{
		if (active)
			c1->player_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
	}

};