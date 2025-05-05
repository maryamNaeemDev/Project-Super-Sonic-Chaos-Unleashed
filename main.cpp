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
int h;
using namespace sf;
using namespace std;

int screen_x = 1200;
int screen_y = 900;

// prototypes 

void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size, Sprite& brickSp1, Sprite& brickSp2, Sprite& brickSp3, Sprite spikeSp, Sprite leafsprite, Sprite brickSp4, Sprite lionspriteRt, Sprite lionsprite, Sprite crystalsp);

void movePlayer(float& player_x, float& player_y, float jumpStrength, Clock& delayjump, bool& onGround, float& velocityY, char& bottom_left_down, char& bottom_right_down, char** lvl, char& top_mid_up);

void moveView(View& view, float player_x, float player_y, FloatRect& cameraview);

void freeRings(Rings**& ringArray, int& ringCount);

void freeBoast(Boast**& BoastArray, int& BoastCount);

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
	//breakbale wall tex and sprite
	Texture brickTx4;
	Sprite brickSp4;
	//spkie png
	Texture spikeTx;
	Sprite spikeSp;
	//decor sprites
	Texture leafT;
	Sprite  leafsprite;
	//decor sprite 2
	Texture lionT;
	Sprite  lionsprite;
	Texture lionTRt;
	Sprite  lionspriteRt;
	//decor: crystal
	Texture crystaltex;
	Sprite  crystalsp;
	//loading enemy sprites
	MottoBug mottobug(64 * 72, 64 * 9.8, 64 * 86, 64 * 9.8);
	mottobug.setScale(3.0f, 3.0f);

	CrabMeat crab(64 * 96, 64 * 9.6, 64 * 105, 64 * 9.6);
	crab.setScale(3.0f, 3.0f);

	BeeBot beebot(64 * 124, 64 * 4, 64 * 135, 64 * 4);
	beebot.setScale(3.0f, 3.0f);

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

	Rings obj_ring;

	Rings** ringArray = nullptr;
	ringArray = new Rings * [200];

	//for rings display
	int ringCount = 0;
	obj_ring.initializeGrid(lvl, height, width);
	obj_ring.placeOnGrid(lvl, 14, 200, ringArray, ringCount);
	//for pu display
	Boast obj_boast;
	Boast** boastArray = nullptr;
	boastArray = new Boast * [200];
	int boastCount = 0;
	obj_boast.initializeGrid(lvl, height, width);
	obj_boast.placeOnGrid(lvl, 14, 200, boastArray, boastCount);

	//for life display
	Life obj_life;
	Life** lifeArray = nullptr;
	lifeArray = new Life * [200];
	int lifeCount = 0;

	obj_life.initializeGrid(lvl, height, width);
	obj_life.placeOnGrid(lvl, 14, 200, lifeArray, lifeCount);

	for (int j = 0; j < width; j++)
	{
		lvl[0][j] = 'w';
		lvl[8][21] = 'w';
		lvl[8][22] = 'w';
		lvl[8][25] = 'w';
		lvl[8][26] = 'w';
		for (int k = 0; k < 3; k++)
		{
			lvl[height - 4 - k][14] = 'w';
		}
		//adding obstacles
		//mainly blocks
		//in the array the first element is the y axis
		// the second element is the x axis
		for (int k = 0; k < 3; k++)
		{
			lvl[height - 6][16 + k] = 'w';
			lvl[1][16] = 'w';
			lvl[1][16 + 1] = 'w';
			lvl[2][16 + 1] = 'w';

			lvl[1][24 + k] = 'l';

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
		lvl[height - 5][32] = 'o';
		//lvl[height - 4][33] = 'o';
		for (int k = 0; k < 11; k++)
		{
			if (k > 2 && k < 7)
			{
				lvl[k][34] = 'b';
				lvl[k][35] = 'b';
				lvl[k][36] = 'b';
				lvl[k][42] = 'b';
			}
			else {
				lvl[k][34] = 'w';
				lvl[k][35] = 'w';
				lvl[k][36] = 'w';
				lvl[k][42] = 'w';
			}


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
				if (k > 2 && k < 6) {
					lvl[k][62] = 'w';
					lvl[k][63] = 'w';
					lvl[k][64] = 'w';
				}
				else
				{
					lvl[k][62] = 'w';
					lvl[k][63] = 'w';
					lvl[k][64] = 'w';
				}
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
		lvl[height - 4][49] = 'c';
		//lvl[height - 4][50] = 'c';
		lvl[height - 4][60] = 'c';
		//lvl[height - 4][62] = 'c';
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
			lvl[1][89 + i] = 'l';
			if (i < 8) {
				lvl[1][100 + i] = 'l';
			}
			if (i > 6 && i < 12)
			{

				lvl[i][89] = 'b';
				lvl[i][90] = 'b';
				lvl[i][88] = 'b';
			}
			else
			{
				lvl[i][89] = 'q';
				lvl[i][90] = 'q';
				lvl[i][88] = 'q';
			}
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
			lvl[9][141] = 'b';
			lvl[10][141] = 'b';
			//lvl[11][141] = 'b';
			if (k > 5 && k < 12)
			{
				lvl[k][139] = 'b';
				lvl[k][140] = 'b';
				lvl[k][141] = 'b';
			}
			else
			{
				lvl[k][139] = 'w';
				lvl[k][140] = 'w';
				lvl[k][141] = 'w';
			}
			lvl[k][147] = 'w';
			//42=147
			for (int i = 0; i < 5; i++)
			{
				lvl[1][147] = 'w';
				lvl[1][142 + i] = 'w';
				lvl[2][142 + i] = 'w';

				//lvl[height - 4][142] = 'w';
				if (i < 5)
				{//spikes in the region
					lvl[height - 10][142 + i] = 'p';
				}

				//lvl[height - 5][141] = 'w';

				lvl[height - 11][142 + i] = 'w';
				lvl[height - 9][142 + i] = 'w';
				lvl[3][137] = 'o';
				lvl[3][148] = 'O';
				lvl[height - 4][144] = 'p';
				if (i < 4)
				{
					lvl[height - 7][147 + i] = 'b';

					lvl[height - 6][147 + i] = 'b';
					lvl[height - 5][147 + i] = 'b';
					lvl[height - 4][147 + i] = 'b';
					lvl[6][168 + i] = 'b';
				}
				//46=151
				lvl[height - 8][147] = 'b';
				lvl[height - 6][151] = 'b';
				lvl[height - 5][151] = 'b';
				lvl[height - 5][152] = 'w';
				lvl[height - 4][151] = 'b';
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

			lvl[6][180] = 'w';
			lvl[6][183] = 'w';
			lvl[6][186] = 'w';



		}


	}
	/*ring.placeOnGrid(lvl, height, width);*/
	//Textures and sprites loading
	wallTex1.loadFromFile("Data/Bg2.png");
	wallSprite1.setTexture(wallTex1);


	brickTx1.loadFromFile("Data/brick2.png");
	brickSp1.setTexture(brickTx1);

	brickTx2.loadFromFile("Data/brick3.png");
	brickSp2.setTexture(brickTx2);

	brickTx3.loadFromFile("Data/brick1.png");
	brickSp3.setTexture(brickTx3);

	sf::Vector2f scaleFactorL = { 2.0f, 2.0f };
	lionT.loadFromFile("Data/decor/decor 4.png");
	lionsprite.setTexture(lionT);
	scaleFactorL.x = 2.5f;
	scaleFactorL.y = 2.5f;
	lionsprite.setScale(scaleFactorL);
	lionTRt.loadFromFile("Data/decor/decor 4(rt).png");
	lionspriteRt.setTexture(lionTRt);
	scaleFactorL.x = 2.5f;
	scaleFactorL.y = 2.5f;
	lionspriteRt.setScale(scaleFactorL);


	sf::Vector2f scaleFactorB = { 2.0f, 2.0f };
	brickTx4.loadFromFile("Data/decor/breakablewall.png");
	brickSp4.setTexture(brickTx4);
	scaleFactorB.x = 2.0f;
	scaleFactorB.y = 2.0f;
	brickSp4.setScale(scaleFactorB);

	spikeTx.loadFromFile("Data/spike.png");
	spikeSp.setTexture(spikeTx);

	crystaltex.loadFromFile("Data/crystal.png");
	crystalsp.setTexture(crystaltex);

	sf::Vector2f scaleFactor = { 1.0f, 1.0f };
	leafT.loadFromFile("Data/decor/decor1.png");
	leafsprite.setTexture(leafT);
	scaleFactor.x = 2.0f;
	scaleFactor.y = 2.5f;
	leafsprite.setScale(scaleFactor);

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
	FloatRect cameraview(0, 0, 400 + 90 + 90 + 5 , 200 + 50 + 50 + 10);

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

	bool t;
	bool s=true;
	bool k;
	

	Sonic* sonic;
	sonic = new Sonic;
	Player player(sonic);
	Knuckles* knuckles;
	knuckles = new Knuckles;
	Computer_Controlled c1(knuckles, sonic);
	Tails* tails;
	tails = new Tails;
	Computer_Controlled c2(tails, knuckles);

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

		player.apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		c1.apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		c2.apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		window.clear();

		display_level(window, height, width, lvl, wallSprite1, cell_size, brickSp1, brickSp2, brickSp3, spikeSp, leafsprite, brickSp4, lionspriteRt, lionsprite, crystalsp);
		moveView(view, player.getX(), player.getY(), cameraview);
		player.animate(toggle, boggle);
		c1.animate(toggle, boggle);
		c2.animate(toggle, boggle);
		player.draw(window);
		c1.draw(window);
		c2.draw(window);
		player.move(lvl, cell_size, width);
		c1.update(lvl, cell_size, width, height);
		c2.update(lvl, cell_size, width, height);
		
		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			player.active_character(tails);
			c1.computercontrol(sonic, tails);
			c2.computercontrol(knuckles, sonic);
			t = true;
			k = false;
			s = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::K))
		{
			player.active_character(knuckles);
			c1.computercontrol(sonic, tails);
			c2.computercontrol(tails, knuckles);
			t = false;
			k = true;
			s = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player.active_character(sonic);
			c1.computercontrol(knuckles, sonic);
			c2.computercontrol(tails, knuckles);
			t = false;
			k = false;
			s = true;
		}
		if (k)
		{
			knuckles->breakwall(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		}
		if (t)
		{
			tails->fly(lvl, cell_size);
		}
		mottobug.update();
		mottobug.render(window);
		crab.update();
		crab.render(window);
		beebot.update();
		beebot.render(window);
		for (int i = 0; i < ringCount; ++i) {
			ringArray[i]->setScaleC(0.75f, 0.75f);
			ringArray[i]->update();
			ringArray[i]->render(window);
		}
		for (int i = 0; i < boastCount; ++i) {
			boastArray[i]->setScaleC(0.75f, 0.75f);
			boastArray[i]->update();
			boastArray[i]->render(window);
		}
		for (int i = 0; i < lifeCount; ++i) {
			lifeArray[i]->setScaleC(0.75f, 0.75f);
			lifeArray[i]->update();
			lifeArray[i]->render(window);
		}
		window.setView(view);
		window.display();
	}
	freeRings(ringArray, ringCount);
	freeBoast(boastArray, boastCount);
	for (int i = 0; i < lifeCount; ++i) {
		delete lifeArray[i];
	}
	delete[] lifeArray;
	lifeArray = nullptr;
	lifeCount = 0;

	delete sonic;
	delete knuckles;
	delete tails;
	return 0;
}


// functions



void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size, Sprite& brickSp1, Sprite& brickSp2, Sprite& brickSp3, Sprite spikeSp, Sprite leafsprite, Sprite brickSp4, Sprite lionspriteRt, Sprite lionsprite, Sprite crystalsp)
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
			else if (lvl[i][j] == 'b')
			{
				brickSp4.setPosition(j * cell_size, i * cell_size);  // Position the bricks properly
				//cout << "Drawing brick at: " << j << ", " << i << endl;
				window.draw(brickSp4);
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
			else if (lvl[i][j] == 'l')
			{
				leafsprite.setPosition(j * cell_size, i * cell_size);
				window.draw(leafsprite);
			}

			else if (lvl[i][j] == 'o')
			{
				lionsprite.setPosition(j * 64, i * 64);  // Position the bricks properly
				//cout << "Drawing brick at: " << j << ", " << i << endl;
				window.draw(lionsprite);
			}
			else if (lvl[i][j] == 'O')
			{
				lionspriteRt.setPosition(j * cell_size, i * cell_size);  // Position the bricks properly
				//cout << "Drawing brick at: " << j << ", " << i << endl;
				window.draw(lionspriteRt);
			}
			else if (lvl[i][j] == 'c')
			{
				crystalsp.setPosition(j * cell_size, i * cell_size);  // Position the bricks properly
				//cout << "Drawing brick at: " << j << ", " << i << endl;
				window.draw(crystalsp);
			}




		}
	}
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
		if (player_y-30 > cameraview.top + cameraview.height)
			view.move(0, player_y - (cameraview.top + cameraview.height));
	}
}

void freeRings(Rings**& ringArray, int& ringCount) {
	for (int i = 0; i < ringCount; ++i) {
		delete ringArray[i];
	}
	delete[] ringArray;
	ringArray = nullptr;
	ringCount = 0;
}
void freeBoast(Boast**& BoastArray, int& BoastCount) {
	for (int i = 0; i < BoastCount; ++i) {
		delete BoastArray[i];
	}
	delete[] BoastArray;
	BoastArray = nullptr;
	BoastCount = 0;
}