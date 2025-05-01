#include <iostream>
#include <fstream>
#include <cstdlib> //for rand func
#include <ctime> //for srand func
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"enemies.h"
int h;
using namespace sf;
using namespace std;

int screen_x = 1200;
int screen_y = 900;

// prototypes 
void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth);

void draw_player(RenderWindow& window, Sprite& RstillSprite, Sprite& LstillSprite, float player_x, float player_y, Sprite& leftjog, Sprite& rightjog, bool& switche, bool& twitche, bool& bruh, bool& truh, Sprite& leftup, Sprite& rightup);

void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size, Sprite& brickSp1, Sprite& brickSp2, Sprite& brickSp3, Sprite spikeSp);

void movePlayer(float& player_x, float& player_y, float jumpStrength, Clock& delayjump, bool& onGround, float& velocityY, char& bottom_left_down, char& bottom_right_down, char** lvl, char& top_mid_up, bool& switche, bool& twitche, const int cell_size, const int height, const int width, bool& bruh, bool& truh);

void animation(Sprite& LstillSprite, Sprite& leftjog, Texture& leftjog1, Texture& leftjog2, Texture& leftjog3, Texture& leftjog4, Texture& leftjog5, Texture& leftjog6, Texture& leftjog7, Texture& leftjog8, Texture& leftjog9, Texture& leftjog10, Sprite& rightjog, Texture& rightjog1, Texture& rightjog2, Texture& rightjog3, Texture& rightjog4, Texture& rightjog5, Texture& rightjog6, Texture& rightjog7, Texture& rightjog8, Texture& rightjog9, Texture& rightjog10, float scale_x, float scale_y, bool& switche, bool& twitche, bool toggle[], Sprite& leftup, Texture& leftup1, Texture& leftup2, Texture& leftup3, Texture& leftup4, Texture& leftup5, Texture& leftup6, Texture& leftup7, Texture& leftup8, Sprite& rightup, Texture& rightup1, Texture& rightup2, Texture& rightup3, Texture& rightup4, Texture& rightup5, Texture& rightup6, Texture& rightup7, Texture& rightup8, bool boggle[], bool& bruh);

void moveView(View& view, float player_x, float player_y, FloatRect& cameraview);
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
	const int width = 200;

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
	lvlMus.setVolume(0);
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
		for (int k = 0; k < 3; k++)
		{
			lvl[height - 4 - k][14] = 'w';
		}
		//adding obstacles
		//mainly blocks
		//in the array the first element is the y axis
		// the second element is the z axis
		for (int k = 0; k < 3; k++)
		{
			lvl[height - 6][16 + k] = 'w';
			lvl[1][16] = 'w';
			lvl[1][16 + 1] = 'w';
			lvl[2][16 + 1] = 'w';
		}
		for (int k = 0; k < 3; k++)
		{
			lvl[height - 6][20 + k] = 'w';
			lvl[1][16 + 1] = 'w';
			lvl[2][16 + 1] = 'w';
			lvl[1][16 + 1] = 'w';

		}


		for (int k = 0; k < 3; k++)
		{
			lvl[height - 6][25 + k] = 'w';
			lvl[1][20] = 'w';
			lvl[1][20 + 1] = 'w';
			lvl[2][20 + 1] = 'w';
			lvl[1][20 + 2] = 'w';
			lvl[10][19 + k] = 'p';

		}
		for (int k = 0; k < 3; k++)
		{
			lvl[height - 6][31 + k] = 'w';


		}
		//knuckles region
		//wall breaking
		for (int k = 0; k < 11; k++)
		{
			lvl[k][34] = 'w';
			lvl[k][35] = 'w';
			lvl[k][36] = 'w';

			lvl[k][42] = 'w';

			for (int i = 0; i < 5; i++)
			{
				lvl[1][42] = 'w';
				lvl[1][37 + i] = 'w';
				lvl[2][37 + i] = 'w';

				lvl[height - 4][36] = 'w';
				if (i < 5)
				{//spikes in the region
					lvl[height - 4][37 + i] = 'p';
				}

				lvl[height - 5][36] = 'w';


				lvl[height - 7][37 + i] = 'w';

				lvl[height - 8][39] = 'p';
				if (i < 4)
				{
					lvl[height - 7][42 + i] = 'w';

					lvl[height - 6][42 + i] = 'w';
					lvl[height - 5][42 + i] = 'w';
					lvl[height - 4][42 + i] = 'w';

				}
				lvl[height - 6][46] = 'w';
				lvl[height - 5][46] = 'w';
				lvl[height - 5][47] = 'w';
				lvl[height - 4][46] = 'w';
				lvl[height - 4][47] = 'w';
				lvl[height - 4][48] = 'w';

			}
			if (k != 1 && k != 2 && k != 3)
			{
				lvl[k][62] = 'w';
				lvl[k][63] = 'w';
				lvl[k][64] = 'w';
			}


		}
		// platforms pit beneath
		for (int i = 0; i < 3; i++)
		{
			lvl[height - 6][51 + i] = 'w';
			lvl[height - 8][55 + i] = 'w';
			lvl[height - 10][59 + i] = 'w';
			lvl[6][90 + i] = 'w';
		}
		//motto bug enemy zone
		for (int i = 0; i < 9; i++)
		{
			lvl[height - 2][51 + i] = ' ';
			lvl[height - 1][51 + i] = ' ';
			//lvl[height-3 ][51 + i] = ' ';
		}

		lvl[height - 1][j] = 'q';
		lvl[height - 3][j] = 'w';
		lvl[height - 2][j] = 'q';
		for (int i = 0; i < 20; i++)
		{
			lvl[1][68 + i] = 'q';
			lvl[2][68 + i] = 'q';
		}
		for (int k = 0; k < 2; k++)
		{
			lvl[height - 8][68 + k] = 'w';
			lvl[height - 8][73 + k] = 'w';
			lvl[height - 8][81 + k] = 'w';
			lvl[height - 8][86 + k] = 'w';
		}
		for (int i = 0; i < 11; i++)
		{
			lvl[i][89] = 'q';
			lvl[i][90] = 'q';
			lvl[i][88] = 'q';
		}
		//all the pits logic here
		for (int i = 0; i < 15; i++)
		{
			lvl[height - 2][91 + i] = ' ';
			lvl[height - 1][91 + i] = ' ';
			//lvl[height-3 ][51 + i] = ' ';
			//lvl[height - 2][116 + i] = ' ';
			//lvl[height - 2][172 + i] = ' ';
			////lvl[height - 3][172 + i] = ' ';
		}

		//stairs for mid level mini boss fight
		for (int i = 0; i < 7; i++)
		{
			lvl[height - 4][107 + i] = 'w';
			if (i < 6)
				lvl[height - 5][108 + i] = 'w';
			if (i < 5)
				lvl[height - 6][109 + i] = 'w';
			if (i < 4)
				lvl[height - 7][110 + i] = 'w';
			if (i < 3)
				lvl[height - 8][111 + i] = 'w';
			if (i < 2)
				lvl[height - 9][112 + i] = 'w';
			if (i < 1)
				lvl[height - 10][113 + i] = 'w';
			//make it height -1 when fully implementing
			lvl[height - 2][131 + i] = ' ';
			//lvl[height - 2][131 + i] = ' ';
		/*	lvl[height - 2][187 + i] = ' ';
			lvl[height - 1][187 + i] = ' ';*/
		}
		//wall breaking pt 2
		for (int k = 0; k < 11; k++)
		{
			lvl[k][139] = 'w';
			lvl[k][140] = 'w';
			lvl[k][141] = 'w';

			lvl[k][147] = 'w';
			//42=147
			for (int i = 0; i < 5; i++)
			{
				lvl[1][147] = 'w';
				lvl[1][142 + i] = 'w';
				lvl[2][142 + i] = 'w';

				lvl[height - 4][141] = 'w';
				if (i < 5)
				{//spikes in the region
					lvl[height - 10][142 + i] = 'p';
				}

				lvl[height - 5][141] = 'w';

				lvl[height - 11][142 + i] = 'w';
				lvl[height - 9][142 + i] = 'w';

				lvl[height - 4][144] = 'p';
				if (i < 4)
				{
					lvl[height - 7][147 + i] = 'w';

					lvl[height - 6][147 + i] = 'w';
					lvl[height - 5][147 + i] = 'w';
					lvl[height - 4][147 + i] = 'w';

				}
				//46=151
				lvl[height - 6][151] = 'w';
				lvl[height - 5][151] = 'w';
				lvl[height - 5][152] = 'w';
				lvl[height - 4][151] = 'w';
				lvl[height - 4][152] = 'w';
				lvl[height - 4][153] = 'w';

			}
			//bees round
			for (int i = 0; i < 8; i++)
			{
				lvl[4][159 + i] = 'q';
				lvl[5][159 + i] = 'q';
			}
			lvl[6][158] = 'q';
			lvl[6][167] = 'q';



		}


	}
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

	///////////////////////////////////////
	//eneimies declaration
	//start x,starty, end x and end y
	MottoBug mottobug(64 * 69, 64 * 9.8, 64 * 86, 64 *9.8);
	mottobug.setScale(3.0f, 3.0f); 
	mottobug.loadSprite("Data/Enemies/mottobug1.png"); // Path to your MottoBug sprite

	////////////////////////////////////////////////////////
	float player_x = 100;
	float player_y = 100;

	float max_speed = 15;

	float velocityX = 0;
	float velocityY = 0;

	float jumpStrength = -20; // Initial jump velocity
	float gravity = 1;  // Gravity acceleration

	

	//SPrites for sonic!!
	Texture LstillTex;
	Sprite LstillSprite;
    Texture RstillTex;
Sprite RstillSprite;
bool bruh;
bool truh;


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

float scale_x = 2.5;
float scale_y = 2.5;

LstillTex.loadFromFile("Data/0left_still.png");
LstillSprite.setTexture(LstillTex);
LstillSprite.setScale(scale_x, scale_y);

RstillTex.loadFromFile("Data/0right_still.png");
RstillSprite.setTexture(RstillTex);
RstillSprite.setScale(scale_x, scale_y);

bool switche, twitche;
leftjog1.loadFromFile("Data/leftjog1.png");
leftjog2.loadFromFile("Data/leftjog2.png");
leftjog3.loadFromFile("Data/leftjog3.png");
leftjog4.loadFromFile("Data/leftjog4.png");
leftjog5.loadFromFile("Data/leftjog5.png");
leftjog6.loadFromFile("Data/leftjog6.png");
leftjog7.loadFromFile("Data/leftjog7.png");
leftjog8.loadFromFile("Data/leftjog8.png");
leftjog9.loadFromFile("Data/leftjog9.png");
leftjog10.loadFromFile("Data/leftjog10.png");

rightjog1.loadFromFile("Data/rightjog1.png");
rightjog2.loadFromFile("Data/rightjog2.png");
rightjog3.loadFromFile("Data/rightjog3.png");
rightjog4.loadFromFile("Data/rightjog4.png");
rightjog5.loadFromFile("Data/rightjog5.png");
rightjog6.loadFromFile("Data/rightjog6.png");
rightjog7.loadFromFile("Data/rightjog7.png");
rightjog8.loadFromFile("Data/rightjog8.png");
rightjog9.loadFromFile("Data/rightjog9.png");
rightjog10.loadFromFile("Data/rightjog10.png");

leftup1.loadFromFile("Data/leftup1.png");
leftup2.loadFromFile("Data/leftup2.png");
leftup3.loadFromFile("Data/leftup3.png");
leftup4.loadFromFile("Data/leftup4.png");
leftup5.loadFromFile("Data/leftup5.png");
leftup6.loadFromFile("Data/leftup6.png");
leftup7.loadFromFile("Data/leftup7.png");
leftup8.loadFromFile("Data/leftup8.png");

rightup1.loadFromFile("Data/rightup1.png");
rightup2.loadFromFile("Data/rightup2.png");
rightup3.loadFromFile("Data/rightup3.png");
rightup4.loadFromFile("Data/rightup4.png");
rightup5.loadFromFile("Data/rightup5.png");
rightup6.loadFromFile("Data/rightup6.png");
rightup7.loadFromFile("Data/rightup7.png");
rightup8.loadFromFile("Data/rightup8.png");

bool toggle[10] = { 0 };
int i = 0;

bool boggle[8] = { 0 };
int j = 0;
    



	bool onGround = false;

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

	char top_left_up = lvl[(int)(offset_y + hit_box_factor_y) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];
	char top_right_up = lvl[(int)(offset_y + hit_box_factor_y) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];
	char top_mid_up = lvl[(int)(offset_y + hit_box_factor_y) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size];
	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size];


	Clock delayjump;

	//LstillTex.loadFromFile("Data/0right_still.png");
	//LstillSprite.setTexture(LstillTex);
	//LstillSprite.setScale(scale_x, scale_y);

	////////////////////////////////////////////////////////
	sf::RectangleShape cameraBox;
	cameraBox.setSize(sf::Vector2f(cameraview.width, 900 - cameraview.height));
	cameraBox.setFillColor(sf::Color(0, 255, 0, 50));  // Semi-transparent green
	cameraBox.setOutlineColor(sf::Color::Green);
	cameraBox.setOutlineThickness(2);

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
///// PARTTT OF ANIMATIONSSSSS ////////

		player_gravity(lvl, offset_y, velocityY, onGround, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, player_x, player_y, cell_size, Pheight, Pwidth);

		window.clear();

		display_level(window, height, width, lvl, wallSprite1, cell_size, brickSp1, brickSp2, brickSp3, spikeSp);
		moveView(view, player_x, player_y, cameraview);
		animation(LstillSprite, leftjog, leftjog1, leftjog2, leftjog3, leftjog4, leftjog5, leftjog6, leftjog7, leftjog8, leftjog9, leftjog10, rightjog, rightjog1, rightjog2, rightjog3, rightjog4, rightjog5, rightjog6, rightjog7, rightjog8, rightjog9, rightjog10, scale_x, scale_y, switche, twitche, toggle, leftup, leftup1, leftup2, leftup3, leftup4, leftup5, leftup6, leftup7, leftup8, rightup, rightup1, rightup2, rightup3, rightup4, rightup5, rightup6, rightup7, rightup8, boggle, bruh);
		draw_player(window, RstillSprite, LstillSprite, player_x, player_y, leftjog, rightjog, switche, twitche, bruh, truh, leftup, rightup);
		movePlayer(player_x, player_y, jumpStrength, delayjump, onGround, velocityY, bottom_left_down, bottom_right_down, lvl, top_mid_up, switche, twitche, cell_size, height, width, bruh, truh);

		mottobug.update();
		mottobug.render(window);
		window.setView(view);
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
	// Top-left corner check (top edge of the player's hitbox)
	char top_left_up = lvl[(int)(offset_y + hit_box_factor_y) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];

	// Top-right corner check (top edge of the player's hitbox)
	char top_right_up = lvl[(int)(offset_y + hit_box_factor_y) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];

	// Top-middle check (center-top of the player's hitbox)
	char top_mid_up = lvl[(int)(offset_y + hit_box_factor_y) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size];

	/*if (top_left_up == 'w' || top_mid_up == 'w' || top_right_up == 'w')
	{
		player_y -= 70;
	}*/

	if (velocityY >= 0)
	{
		if (bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w')
		{
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
void draw_player(RenderWindow& window, Sprite& RstillSprite, Sprite& LstillSprite, float player_x, float player_y, Sprite& leftjog, Sprite& rightjog, bool& switche, bool& twitche, bool& bruh, bool& truh, Sprite& leftup, Sprite& rightup) 
{
	if (switche)
	{
		//cout << "X:" << player_x << "  Y:" << player_y << endl;
		leftjog.setPosition(player_x, player_y);
		window.draw(leftjog);
		bruh = true;
	}
	else if (twitche)
	{
		cout << "X:" << player_x << "  Y:" << player_y << endl;
		rightjog.setPosition(player_x, player_y);
		window.draw(rightjog);
	}
	else
	{
		if (bruh)
		{
			//cout << "X:" << player_x << "  Y:" << player_y << endl;
			if (truh)
			{
				cout << "UPPPPP"<<endl;
				leftup.setPosition(player_x, player_y);
				window.draw(leftup);
			}
			else
			{
				LstillSprite.setPosition(player_x, player_y);
				window.draw(LstillSprite);
			}
			
		}
		else
		{
			if (truh)
			{
				cout << "UPPPPP" << endl;
				rightup.setPosition(player_x, player_y);
				window.draw(rightup);
			}
			else
			{
				RstillSprite.setPosition(player_x, player_y);
				window.draw(RstillSprite);
			}
		}
	}

}
void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size, Sprite& brickSp1, Sprite& brickSp2, Sprite& brickSp3, Sprite spikeSp)
{

	for (int x = 0; x < 12800; x += 1600) {

		wallSprite1.setPosition(x, 0);
		window.draw(wallSprite1);
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
			if (j == 0 || j == width - 1)
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
			else if (i == 10 && j == 4)
			{
				spikeSp.setPosition(j * cell_size, i * cell_size);
				window.draw(spikeSp);
			}
			else if (lvl[i][j] == 'p')
			{
				spikeSp.setPosition(j * cell_size, i * cell_size);
				window.draw(spikeSp);
			}


		}
	}
}

void animation(Sprite& LstillSprite, Sprite& leftjog, Texture& leftjog1, Texture& leftjog2, Texture& leftjog3, Texture& leftjog4, Texture& leftjog5, Texture& leftjog6, Texture& leftjog7, Texture& leftjog8, Texture& leftjog9, Texture& leftjog10, Sprite& rightjog, Texture& rightjog1, Texture& rightjog2, Texture& rightjog3, Texture& rightjog4, Texture& rightjog5, Texture& rightjog6, Texture& rightjog7, Texture& rightjog8, Texture& rightjog9, Texture& rightjog10, float scale_x, float scale_y, bool& switche, bool& twitche, bool toggle[], Sprite& leftup, Texture& leftup1, Texture& leftup2, Texture& leftup3, Texture& leftup4, Texture& leftup5, Texture& leftup6, Texture& leftup7, Texture& leftup8, Sprite& rightup, Texture& rightup1, Texture& rightup2, Texture& rightup3, Texture& rightup4, Texture& rightup5, Texture& rightup6, Texture& rightup7, Texture& rightup8, bool boggle[], bool& bruh)
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
	}
}

void movePlayer(float& player_x, float& player_y, float jumpStrength, Clock& delayjump, bool& onGround, float& velocityY, char& bottom_left_down, char& bottom_right_down, char** lvl, char& top_mid_up, bool& switche, bool& twitche, const int cell_size, const int height, const int width, bool& bruh, bool& truh)
{
	Keyboard key;
	// Calculate player's grid position (for collision checks)
	int gridX = static_cast<int>(player_x) / cell_size;
	int gridY = static_cast<int>(player_y) / cell_size;
	if (key.isKeyPressed(key.Left))
	{
		if (gridX > 0 && lvl[gridY][gridX] != 'w')
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
	else if (key.isKeyPressed(key.Right))
	{
		if (gridX < width - 1 && lvl[gridY][gridX+2] != 'w')
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
	else
	{
		twitche = false;
		switche = false;
	}
	if (key.isKeyPressed(key.Space) && delayjump.getElapsedTime().asSeconds() > 0.3 && onGround)
	{
		cout << "UPPPPP DETECTION" << endl;
		truh = true;
		velocityY = +jumpStrength;
		delayjump.restart();
	}
	/*if (!onGround && key.isKeyPressed(key.Space))
		truh = true;
	else
		truh = false;*/
	//if (key.isKeyPressed(key.Left)&&onGround&&(lvl[static_cast<int>(player_y)-20][static_cast<int>(player_x+20)]!='w'))


	//if(bottom_right_down=='w')


	//if (key.isKeyPressed(key.Space) && delayjump.getElapsedTime().asSeconds() > 0.3)
	//{

	//	/*Clock delayclock3;*/
	//	cloc = true;
	//	player_y += (jumpStrength);
	//	cout << "here";
	//	//delayjump2.restart();
	//	if (delayjump2.getElapsedTime().asSeconds() > 0.9)
	//	{
	//		delayjump.restart();
	//		delayjump2.restart();
	//		cout << "now here!";
	//	}
	//	//delayjump.restart();
	//}
	/*if (cloc)
	{
		if (delayjump.getElapsedTime().asMicroseconds() > 1)
		{
			player_y += jumpStrength;
			cloc = false;
			delayjump2.restart();
		}
	}*/
}


void moveView(View& view, float player_x, float player_y, FloatRect& cameraview)
{
	Vector2f centre = view.getCenter();
	//Vector2f size = view.getSize();
	cameraview.left = centre.x - cameraview.width / 2;
	cameraview.top = centre.y - cameraview.height / 2;
	if (player_x > 300)
	{
		if (player_x < cameraview.left)
			view.move(player_x - cameraview.left, 0);
		else if (player_x > cameraview.left + cameraview.width)
			view.move(player_x - (cameraview.left + cameraview.width), 0);
		/*if (player_y < cameraview.top)
			view.move(0, player_y - cameraview.top);*/
		if (player_y > cameraview.top + cameraview.height)
			view.move(0, player_y - (cameraview.top + cameraview.height));
	}
}