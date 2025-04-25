#include <iostream>
#include <fstream>
#include <cstdlib> //for rand func
#include <ctime> //for srand func
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

int screen_x = 1200;
int screen_y = 900;

// prototypes 
void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth);

void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y);

void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size, Sprite& brickSp1, Sprite& brickSp2, Sprite& brickSp3, Sprite spikeSp);

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

	// Uppercase for not interactable background accessories

	// C is for crystals

	const int cell_size = 64;
	const int height = 14;
	const int width = 110;

	char** lvl = NULL;
	//wall texture
	Texture wallTex1;
	Sprite wallSprite1;
	//brick texture
	Texture brickTx1;
	Sprite brickSp1;
	//2nd brick texture
	Texture brickTx2;
	Sprite brickSp2;
	//3rd brick texture
	Texture brickTx3;
	Sprite brickSp3;
	//spkie png
	Texture spikeTx;
	Sprite spikeSp;
	//srand(time(0));

	Music lvlMus;

	lvlMus.openFromFile("Data/labrynth.ogg");
	lvlMus.setVolume(30);
	lvlMus.play();
	lvlMus.setLoop(true);

	lvl = new char* [height];
	for (int i = 0; i < height; i += 1)
	{
		lvl[i] = new char[width] {'\0'};
		
	}
	//initializing first and last three rows to w which is for brick
	for (int j = 0; j < width; j++)
	{
		lvl[0][j] = 'w';
		for (int k = 0;k < 3;k++)
		{
			lvl[height - 4 - k][14] = 'w';
		}
		for (int k = 0;k < 9;k++)
		{
			lvl[height - 6][16+k] = 'w';
			if (k>2)
			{
				lvl[height - 6][16 + k+2] = 'w';
			}
		}

		lvl[height - 1][j] = 'q';
		lvl[height - 3][j] = 'w';
	    lvl[height - 2][j] = 'q';
		
	}

	//for background, letting every lvl ==s , because background is at every pixel
	for (int i = 0;i < height;i++)
	{
		for (int j = 0; j < width; j++)
		{
			lvl[i][j] == 's';
		}
	}

	lvl[11][1] = 's';
	lvl[11][2] = 'w';
	lvl[11][3] = 'w';
	//Textures and sprites loading
	wallTex1.loadFromFile("Data/Bg2.png");
	wallSprite1.setTexture(wallTex1);

	brickTx1.loadFromFile("Data/brick2.png");
    brickSp1.setTexture(brickTx1);
	
	brickTx2.loadFromFile("Data/brick3.png");
	brickSp2.setTexture(brickTx2);

	brickTx3.loadFromFile("Data/brick1.png");
	brickSp3.setTexture(brickTx3);
	
	spikeTx.loadFromFile("Data/spike.png");
	spikeSp.setTexture(spikeTx);
	
	////////////////////////////////////////////////////////
	float player_x = 100;
	float player_y = 100;

	float max_speed = 15;

	float velocityX = 0;
	float velocityY = 0;

	float jumpStrength = -20; // Initial jump velocity
	float gravity = 1;  // Gravity acceleration

	Texture LstillTex;
	Sprite LstillSprite;

	bool onGround = false;

	float offset_x = 0;
	float offset_y = 0;

	float terminal_Velocity = 20;

	float acceleration = 0.2;

	float scale_x = 2.5;
	float scale_y = 2.5;

	////////////////////////////
	int raw_img_x = 24;
	int raw_img_y = 35;

	int Pheight = raw_img_y * scale_y;
	int Pwidth = raw_img_x * scale_x;

	//only to adjust the player's hitbox

	int hit_box_factor_x = 8 * scale_x;
	int hit_box_factor_y = 5 * scale_y;

	LstillTex.loadFromFile("Data/0right_still.png");
	LstillSprite.setTexture(LstillTex);
	LstillSprite.setScale(scale_x, scale_y);

	////////////////////////////////////////////////////////

	Event ev;
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

		player_gravity(lvl, offset_y, velocityY, onGround, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, player_x, player_y, cell_size, Pheight, Pwidth);

		window.clear();

		display_level(window, height, width, lvl, wallSprite1, cell_size,brickSp1,  brickSp2, brickSp3,  spikeSp);
		draw_player(window, LstillSprite, player_x, player_y);

		window.display();
	}


	return 0;
}


// functions

void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth)
{
	offset_y = player_y;

	offset_y += velocityY;

	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size];


	if (bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w')
	{
		onGround = true;
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
void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y) {

	LstillSprite.setPosition(player_x, player_y);
	window.draw(LstillSprite);

}
void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size, Sprite& brickSp1, Sprite& brickSp2 , Sprite& brickSp3, Sprite spikeSp)
{
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			if (lvl[i][j]=='s')
			{
				wallSprite1.setPosition(0, 0);  // Position the background tiles properly
				window.draw(wallSprite1);
			}
			
			
		}
	}
	//logic for a random pattern for bricks in last 2 rows
	//this pattern is repeated in every frame
	int qIndex = 0;
	string pattern = "232223"; // or generate this randomly once
	int patternLen = pattern.length();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j==width-1)
			{
				brickSp1.setPosition(j * cell_size, i * cell_size);  // Position the bricks properly
				//cout << "Drawing brick at: " << j  << ", " << i  << endl;
				window.draw(brickSp1);
			}
			if (lvl[i][j] == 'w')
			{
				
				brickSp1.setPosition(j * cell_size, i * cell_size);  // Position the bricks properly
				//cout << "Drawing brick at: " << j  << ", " << i  << endl;
				window.draw(brickSp1);
			}
			else if (lvl[i][j] == 'q') 
			{
				char brickType = pattern[qIndex % patternLen];
				if (brickType == '2') {
					brickSp2.setPosition(j * cell_size, i * cell_size);
					window.draw(brickSp2);
				}
				
				else {
					brickSp3.setPosition(j * cell_size, i * cell_size);
					window.draw(brickSp3);
				}
				qIndex++;
				
			}
			else if (i==10 && j==4)
			{
				spikeSp.setPosition(j * cell_size, i * cell_size);
				window.draw(spikeSp);
			}
			
		}
	}
}