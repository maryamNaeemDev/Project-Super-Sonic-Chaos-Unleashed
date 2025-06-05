#pragma once
#include<iostream>
#include"enemies.h"
#include"character.h"
#include"collectables.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class Level4;
class Levels
{
protected:
	int ringCount = 0;
	int boastCount = 0;
	int lifeCount = 0;
	const int cell_size = 64;
	const int height = 14;
	//level1=200, level2=255, ;level3=300, level4=19;
	int width = 200;
	float offset_x = 0;
	float offset_y = 0;
	float scale_x = 2.5;
	float scale_y = 2.5;
	float terminal_Velocity = 20;
	float acceleration = 0.2;
	int raw_img_x = 24;
	int raw_img_y = 35;
	int Pheight = raw_img_y * scale_y;
	int Pwidth = raw_img_x * scale_x;
	int hit_box_factor_x = 8 * scale_x;
	int hit_box_factor_y = 5 * scale_y;
	float jumpStrength = -20; // Initial jump velocity
	float gravity = 1;
	int level;
	View view;
	FloatRect* cameraview;
	RenderWindow window;
	RectangleShape cameraBox;


	bool t;
	bool s = true;
	bool k;

	Event ev;

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

	Font font;
	Text scoreText;
	Text livesText;
	Text powerUpText;


	MottoBug* mottobug;

	CrabMeat* crab;

	BeeBot* beebot;

	BatBrain* bat;

	EggStinger* eggstinger;

	Music lvlMus;

	Rings obj_ring;
	Rings** ringArray = nullptr;

	Boast obj_boast;
	Boast** boastArray = nullptr;

	Life obj_life;
	Life** lifeArray = nullptr;




public:
	Levels(int screen_x, int screen_y)
	{
		cameraview = new FloatRect(0, 0, 400 + 90 + 90 + 5, 200 + 50 + 50 + 10);
		view.setViewport(FloatRect(0, 0, 1200, 900));
		view.setSize(screen_x, screen_y);  // Set view size to window size
		view.setCenter(0, 0);              // Initial center position// Apply the view to the window
		cameraBox.setSize(sf::Vector2f(cameraview->width, 900 - cameraview->height));
		cameraBox.setFillColor(sf::Color(0, 255, 0, 50));  // Semi-transparent green
		cameraBox.setOutlineColor(sf::Color::Green);
		cameraBox.setOutlineThickness(2);
		//window->setView(view);

		if (!font.loadFromFile("Data/DungeonFont.ttf")) {  // Make sure you have a font file
			std::cerr << "Failed to load font!" << std::endl;
		}

		// Set up score text
		scoreText.setFont(font);
		scoreText.setCharacterSize(30);
		scoreText.setFillColor(sf::Color::Black);
		scoreText.setPosition(20, 20);

		// Set up lives text
		livesText.setFont(font);
		livesText.setCharacterSize(30);
		livesText.setFillColor(sf::Color::Black);
		livesText.setPosition(20, 50);

		// Set up power-up text
		powerUpText.setFont(font);
		powerUpText.setCharacterSize(30);
		powerUpText.setFillColor(sf::Color::Black);
		powerUpText.setPosition(20, 80);


		lvl = new char* [height];
		

	}

	void updateHUD(Player* player) {
		// Update score
		scoreText.setString("Score: " + std::to_string(player->getScore()));

		// Update lives
		livesText.setString("Lives: " + std::to_string(player->getHp()));

		// Update power-up status
		std::string powerUpStatus = "Power-Up: ";
		if (player->getPowerUp()) {
			powerUpStatus += "Active";
		}
		else {
			powerUpStatus += "Not Active";
		}
		powerUpText.setString(powerUpStatus);

	}

	int getRingCount()
	{
		return ringCount;
	}
	int getWidth() { return width; }
	void moveView(RenderWindow& window, int player_x, int player_y, View& view, FloatRect& cameraview)
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
			if (player_y - 30 > cameraview.top + cameraview.height)
				view.move(0, player_y - (cameraview.top + cameraview.height));
		}
		window.setView(view);
	}
	void freeRings() {
		for (int i = 0; i < ringCount; ++i) {
			delete ringArray[i];
		}
		delete[] ringArray;
		ringArray = nullptr;
		ringCount = 0;
	}
	void freeBoast() {
		for (int i = 0; i < boastCount; ++i) {
			delete boastArray[i];
		}
		delete[] boastArray;
		boastArray = nullptr;
		boastCount = 0;
	}
	void display_level(RenderWindow& window)
	{

		for (int x = 0; x < width * 64; x += 1600) {

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
				if (lvl[i][j] == 'w' || lvl[i][j] == 'j')
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

				else if (lvl[i][j] == 'O')
				{
					lionsprite.setPosition(j * cell_size, i * cell_size);  // Position the bricks properly
					//cout << "Drawing brick at: " << j << ", " << i << endl;
					window.draw(lionsprite);
				}
				else if (lvl[i][j] == 'o')
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
	virtual void runlevel(RenderWindow& window, bool toggle[], bool boggle[], Player* player, Computer_Controlled& c1, Computer_Controlled& c2, Knuckles* knuckles, Sonic* sonic, Tails* tails, View& view, FloatRect& cameraview)
	{
		if (level == 1 && lvlMus.getStatus() != SoundSource::Playing)
		{// if current level is 1 and music is not playing then tis loop would play music
			if (!lvlMus.openFromFile("Data/labrynth.ogg"))
			{
				std::cerr << "Failed to load level 1 music!" << std::endl;
			}
			lvlMus.setVolume(30);
			lvlMus.setLoop(true);
			lvlMus.play();
		}
		///// PARTTT OF ANIMATIONSSSSS ////////

		player->apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		c1.apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		c2.apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		window.clear();
		//sf::Vector2f viewCenter = view.getCenter();
		/*std::cout << "View Center: (" << viewCenter.x << ", " << viewCenter.y << ")\n";
		std::cout << "Player Position: (" << player->getX() << ", " << player->getY() << ")\n";*/
		display_level(window);
		moveView(window, player->getX(), player->getY(), view, cameraview);
		player->animate(toggle, boggle);
		c1.animate(toggle, boggle);
		c2.animate(toggle, boggle);
		player->draw(window);
		c1.draw(window);
		c2.draw(window);
		player->move(lvl, cell_size,  width, offset_y,  hit_box_factor_x,  hit_box_factor_y,  Pheight,  Pwidth);
		c1.update(lvl, cell_size, width, height);
		c2.update(lvl, cell_size, width, height);
		//sf::View view = window.getView();
		//view.setCenter(sf::Vector2f(500.f, 300.f));  // Force view to center on (500, 300)

		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			player->active_character(tails);
			c1.computercontrol(sonic, tails);
			c2.computercontrol(knuckles, sonic);
			t = true;
			k = false;
			s = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::K))
		{
			player->active_character(knuckles);
			c1.computercontrol(sonic, tails);
			c2.computercontrol(tails, knuckles);
			t = false;
			k = true;
			s = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player->active_character(sonic);
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
			tails->fly(lvl, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		}
		if (!mottobug->getDead())
		{
			mottobug->collision(player);
			mottobug->update(player, cell_size);
			mottobug->render(window);
		}
		else
			cout << "IDIEDDDD!!!!";

		if (!crab->getDead())
		{
			crab->collision(player);
			crab->update(player, cell_size);
			crab->render(window);
		}

		if (!beebot->getDead())
		{
			beebot->update(player, cell_size);
			beebot->render(window);
		}
		player->gettingPowerUp();
		player->gettinghurt();
		for (int i = 0; i < ringCount; ++i) {
			if (ringArray[i]->getOn())
			{
				ringArray[i]->setScaleC(0.75f, 0.75f);
				ringArray[i]->update();
				ringArray[i]->collision(player);
				ringArray[i]->render(window);
			}
		}
		for (int i = 0; i < boastCount; ++i) {
			if (boastArray[i]->getOn())
			{
				boastArray[i]->setScaleC(0.75f, 0.75f);
				boastArray[i]->update();
				boastArray[i]->collision(player);
				boastArray[i]->render(window);
			}
		}
		for (int i = 0; i < lifeCount; ++i) {
			if (lifeArray[i]->getOn())
			{
				lifeArray[i]->setScaleC(0.75f, 0.75f);
				lifeArray[i]->update();
				lifeArray[i]->collision(player);
				lifeArray[i]->render(window);
			}
		}
		updateHUD(player);

		window.setView(window.getDefaultView()); // Switch to default view for HUD
		window.draw(scoreText);
		window.draw(livesText);
		window.draw(powerUpText);
		window.setView(view); // Switch back to game view

		window.setView(view);
		window.display();

	}
	/*void killenemies(Player* player)
	{
		if (player->getIsJumping())
		{

		}
	}*/
	~Levels()
	{
		delete mottobug;
		delete beebot;
		delete crab;
		delete bat;
		delete cameraview;
	}

};
class Level1 :public  Levels
{
public:
	Level1(int screen_x, int screen_y) : Levels(screen_x, screen_y)
	{
		width = 200;
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};

		}

		level = 1;
		mottobug = new MottoBug(64 * 72, 64 * 9.8, 64 * 86, 64 * 9.8);
		mottobug->setScale(3.0f, 3.0f);
		crab = new CrabMeat(64 * 96, 64 * 9.6, 64 * 105, 64 * 9.6);
		crab->setScale(3.0f, 3.0f);
		beebot = new BeeBot(64 * 124, 64 * 4, 64 * 135, 64 * 4);
		beebot->setScale(3.0f, 3.0f);

		ringArray = new Rings * [200];
		boastArray = new Boast * [200];
		lifeArray = new Life * [200];

		sf::Vector2f scaleFactorL = { 2.0f, 2.0f };
		lionT.loadFromFile("Data/decor/decor 4(rt).png");
		lionsprite.setTexture(lionT);
		scaleFactorL.x = 2.5f;
		scaleFactorL.y = 2.5f;
		lionsprite.setScale(scaleFactorL);
		lionTRt.loadFromFile("Data/decor/decor 4.png");
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
	}
	~Level1()
	{
		freeRings();
		freeBoast();

		for (int i = 0; i < lifeCount; ++i) {
			delete lifeArray[i];
		}
		delete[] lifeArray;
		for (int i = 0; i < height; i++)
		{
			delete[] lvl[i];
		}
		delete[] lvl;
		lifeArray = nullptr;
		lifeCount = 0;
	}
	void initialization()
	{

		obj_ring.initializeGrid(lvl, height, width, level);
		obj_ring.placeOnGrid(lvl, 14, 250, ringArray, ringCount);
		obj_boast.initializeGrid(lvl, height, width, level);
		obj_boast.placeOnGrid(lvl, 14, 250, boastArray, boastCount);
		obj_life.initializeGrid(lvl, height, width, level);
		obj_life.placeOnGrid(lvl, 14, 250, lifeArray, lifeCount);
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
				lvl[height - 6][16 + k] = 'j';
				lvl[1][16] = 'w';
				lvl[1][16 + 1] = 'w';
				lvl[2][16 + 1] = 'w';

				lvl[1][24 + k] = 'w';

			}

			for (int k = 0; k < 3; k++)
			{
				lvl[height - 6][20 + k] = 'j';
				lvl[1][16 + 1] = 'w';
				lvl[2][16 + 1] = 'w';
				lvl[1][16 + 1] = 'w';

			}


			for (int k = 0; k < 3; k++)
			{
				lvl[height - 6][25 + k] = 'j';
				lvl[1][20] = 'w';
				lvl[1][20 + 1] = 'w';
				lvl[2][20 + 1] = 'w';
				lvl[1][20 + 2] = 'w';
				lvl[10][19 + k] = 'p';

			}
			for (int k = 0; k < 3; k++)
			{
				lvl[height - 6][31 + k] = 'j';


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
				lvl[height - 6][51 + i] = 'j';
				lvl[height - 8][55 + i] = 'j';
				lvl[height - 10][59 + i] = 'j';
				lvl[6][90 + i] = 'j';
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

				lvl[height - 8][68 + k] = 'j';
				lvl[height - 8][73 + k] = 'j';
				lvl[height - 8][81 + k] = 'j';
				lvl[height - 8][86 + k] = 'j';
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

				lvl[6][180] = 'j';
				lvl[6][183] = 'j';
				lvl[6][186] = 'j';



			}


		}
	}


};
class Level2 :public  Levels
{
public:
	Level2(int screen_x, int screen_y) : Levels(screen_x, screen_y)
	{
		level = 2;
		mottobug = new MottoBug(64 * 80, 64 * 8, 64 * 86, 64 * 8);
		mottobug->setScale(3.0f, 3.0f);
		crab = new CrabMeat(64 * 96, 64 * 9.6, 64 * 105, 64 * 9.6);
		crab->setScale(3.0f, 3.0f);
		beebot = new BeeBot(64 * 124, 64 * 4, 64 * 135, 64 * 4);
		beebot->setScale(3.0f, 3.0f);

		bat = new BatBrain(64 * 144, 64 * 1, 64 * 155, 64 * 1);
		bat->setScale(3.0f, 3.0f);

		ringArray = new Rings * [200];
		boastArray = new Boast * [200];
		lifeArray = new Life * [200];

		sf::Vector2f scaleFactorL = { 10.5f, 5.5f };
		lionT.loadFromFile("Data/level2 FS/tornado 2.png");
		lionsprite.setTexture(lionT);
		scaleFactorL.x = 10.5f;
		scaleFactorL.y = 5.5f;
		lionsprite.setScale(scaleFactorL);
		sf::Vector2f scaleFactorL2 = { 10.5f, 5.5f };
		lionTRt.loadFromFile("Data/level2 FS/tornado.png");
		lionspriteRt.setTexture(lionTRt);
		scaleFactorL2.x = 10.5f;
		scaleFactorL2.y = 5.5f;
		lionspriteRt.setScale(scaleFactorL2);


		sf::Vector2f scaleFactorB = { 2.0f, 2.0f };
		brickTx4.loadFromFile("Data/decor/breakablewall.png");
		brickSp4.setTexture(brickTx4);
		scaleFactorB.x = 2.0f;
		scaleFactorB.y = 2.0f;
		brickSp4.setScale(scaleFactorB);

		crystaltex.loadFromFile("Data/crystal.png");
		crystalsp.setTexture(crystaltex);

		sf::Vector2f scaleFactor = { 1.0f, 1.0f };
		leafT.loadFromFile("Data/level2 FS/level (30).png");
		leafsprite.setTexture(leafT);
		scaleFactor.x = 1.0f;
		scaleFactor.y = 1.0f;
		leafsprite.setScale(scaleFactor);

		//Textures and sprites loading
		wallTex1.loadFromFile("Data/bg3.png");
		wallSprite1.setTexture(wallTex1);

		sf::Vector2f scaleFactorP = { 0.5f, 0.5f };
		brickTx1.loadFromFile("Data/level2 FS/level (94).png");
		brickSp1.setTexture(brickTx1);
		scaleFactorP.x = 0.5f;
		scaleFactorP.y = 0.5f;
		lionspriteRt.setScale(scaleFactorP);

		sf::Vector2f scaleFactorI = { 3.5f, 3.5f };
		brickTx2.loadFromFile("Data/level2 FS/ice decor1.png");
		brickSp2.setTexture(brickTx2);
		scaleFactorI.x = 1.0f;
		scaleFactorI.y = 1.0f;
		brickSp2.setScale(scaleFactorI);

		brickTx3.loadFromFile("Data/level2 FS/decor use.png");
		brickSp3.setTexture(brickTx3);
		brickSp3.setScale(scaleFactorI);

		spikeTx.loadFromFile("Data/spike.png");
		spikeSp.setTexture(spikeTx);
	}
	~Level2()
	{
		freeRings();
		freeBoast();
		for (int i = 0; i < lifeCount; ++i) {
			delete lifeArray[i];
		}
		delete[] lifeArray;
		lifeArray = nullptr;
		for (int i = 0; i < height; i++)
		{
			delete[] lvl[i];
		}
		delete[] lvl;
		lifeCount = 0;
	}
	void initialization()
	{
		width = 255;
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};

		}

		obj_ring.initializeGrid(lvl, height, width, level);
		obj_ring.placeOnGrid(lvl, 14, 250, ringArray, ringCount);
		obj_boast.initializeGrid(lvl, height, width, level);
		obj_boast.placeOnGrid(lvl, 14, 250, boastArray, boastCount);
		obj_life.initializeGrid(lvl, height, width, level);
		obj_life.placeOnGrid(lvl, 14, 250, lifeArray, lifeCount);
		for (int j = 0; j < width; j++)
		{  //pit logic
			/*if (j > 30 && j<40)
			{
				lvl[height - 3][j] = ' ';

			}
		else*/
		//{
			lvl[height - 3][j] = 'w';

			//}
			lvl[0][j] = 'l';
			for (int i = 0; i < 9; i++)
			{
				lvl[height - 7][i + 10] = 'j';
				lvl[height - 9][i + 20] = 'j';

			}
			//bee bat region
			for (int i = 0; i < 6; i++)
			{
				lvl[height - 4][i + 40] = 'w';
				lvl[height - 5][i + 42] = 'w';
				lvl[height - 6][i + 44] = 'w';
				lvl[height - 7][i + 46] = 'w';
				lvl[height - 4][i + 70] = 'p';
			}
			for (int i = 0; i < 11; i++)
			{
				if (i < 9)
				{
					lvl[i][63] = 'w';
					lvl[i][64] = 'w';
					lvl[i][65] = 'w';
				}

			}
			for (int i = 0; i < 11; i++)
			{
				lvl[height - 4][i + 78] = 'w';
				lvl[height - 5][i + 78] = 'w';
				if (i < 9)
				{
					lvl[height - 10][i + 78] = 'w';

					lvl[height - 11][i + 78] = 'w';
				}
				lvl[height - 12][i + 78] = 'w';
				lvl[height - 13][i + 78] = 'w';
				lvl[height - 14][i + 78] = 'w';

				lvl[height - 4][i + 92] = 'w';
				lvl[height - 4][i + 92] = 'w';
				lvl[height - 4][i + 92] = 'w';
				lvl[height - 5][i + 92] = 'w';
				//lvl[height - 6][i + 92] = 'w';
				//lvl[height - 7][i + 89] = 'w';
				//lvl[height - 8][i + 89] = 'w';
				//lvl[height - 9][i + 89] = 'w';
				//lvl[height - 10][i + 89] = 'w';
				lvl[height - 11][i + 92] = 'w';
				lvl[height - 12][i + 92] = 'w';
				lvl[height - 13][i + 92] = 'w';
				lvl[height - 14][i + 92] = 'w';

			}

			for (int i = 0; i < 11; i++)
			{
				lvl[height - 4][i + 100] = 'w';
				lvl[height - 5][i + 100] = 'w';
				if (i < 9)
				{
					lvl[height - 10][i + 100] = 'w';
					lvl[height - 11][i + 100] = 'w';
				}
				lvl[height - 12][i + 100] = 'w';
				lvl[height - 13][i + 100] = 'w';
				lvl[height - 14][i + 100] = 'w';
			}
			for (int i = 0; i < 11; i++)
			{
				lvl[height - 4][i + 120] = 'w';
				lvl[height - 5][i + 120] = 'w';
				if (i < 9)
				{
					lvl[height - 10][i + 120] = 'w';
					lvl[height - 11][i + 120] = 'w';
				}
				lvl[height - 12][i + 120] = 'w';
				lvl[height - 13][i + 120] = 'w';
				lvl[height - 14][i + 120] = 'w';
			}
			for (int i = 0; i < 5; i++)
			{
				lvl[height - 7][i + 140] = 'j';
				lvl[height - 7][i + 150] = 'j';
			}
			for (int i = 0; i < 10; i++)
			{
				lvl[height - 4][i + 160] = 'w';
				if (i > 0 && i < 9) {
					lvl[height - 4][i + 161] = 'w';
				}
				if (i > 1 && i < 8)
				{
					lvl[height - 5][i + 162] = 'w';
				}
				if (i > 2 && i < 7)
				{
					lvl[height - 6][i + 163] = 'w';
				}
				if (i > 3 && i < 6)
				{
					lvl[height - 7][i + 164] = 'w';
				}
				if (i > 4 && i < 5)
				{
					lvl[height - 8][i + 165] = 'w';
				}

			}
			lvl[height - 5][175] = 'j';
			lvl[height - 5][180] = 'j';
			lvl[height - 5][185] = 'j';
			lvl[height - 5][190] = 'j';
			lvl[height - 5][195] = 'j';
			lvl[height - 5][200] = 'j';
			lvl[height - 5][205] = 'j';

			lvl[height - 8][173] = 'j';
			lvl[height - 8][177] = 'j';
			lvl[height - 8][183] = 'j';
			lvl[height - 8][187] = 'j';
			lvl[height - 8][193] = 'j';
			lvl[height - 8][197] = 'j';
			lvl[height - 8][203] = 'j';

			lvl[height - 11][175] = 'j';
			lvl[height - 11][180] = 'j';
			lvl[height - 11][185] = 'j';
			lvl[height - 11][190] = 'j';
			lvl[height - 11][195] = 'j';
			lvl[height - 11][200] = 'j';
			lvl[height - 11][205] = 'j';

		}
		lvl[0][220] = 'o';
		lvl[0][240] = 'o';
	}

	void runlevel(RenderWindow& window, bool toggle[], bool boggle[], Player* player, Computer_Controlled& c1, Computer_Controlled& c2, Knuckles* knuckles, Sonic* sonic, Tails* tails, View& view, FloatRect& cameraview)
	{
		if (level == 1 && lvlMus.getStatus() != SoundSource::Playing)
		{// if current level is 1 and music is not playing then tis loop would play music
			if (!lvlMus.openFromFile("Data/labrynth.ogg"))
			{
				std::cerr << "Failed to load level 1 music!" << std::endl;
			}
			lvlMus.setVolume(30);
			lvlMus.setLoop(true);
			lvlMus.play();
		}
		///// PARTTT OF ANIMATIONSSSSS ////////

		player->apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		c1.apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		c2.apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		window.clear();
		//sf::Vector2f viewCenter = view.getCenter();
		/*std::cout << "View Center: (" << viewCenter.x << ", " << viewCenter.y << ")\n";
		std::cout << "Player Position: (" << player->getX() << ", " << player->getY() << ")\n";*/
		display_level(window);
		moveView(window, player->getX(), player->getY(), view, cameraview);
		player->animate(toggle, boggle);
		c1.animate(toggle, boggle);
		c2.animate(toggle, boggle);
		player->draw(window);
		c1.draw(window);
		c2.draw(window);
		player->move(lvl, cell_size, width, offset_y, hit_box_factor_x, hit_box_factor_y, Pheight, Pwidth);
		c1.update(lvl, cell_size, width, height);
		c2.update(lvl, cell_size, width, height);
		//sf::View view = window.getView();
		//view.setCenter(sf::Vector2f(500.f, 300.f));  // Force view to center on (500, 300)

		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			player->active_character(tails);
			c1.computercontrol(sonic, tails);
			c2.computercontrol(knuckles, sonic);
			t = true;
			k = false;
			s = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::K))
		{
			player->active_character(knuckles);
			c1.computercontrol(sonic, tails);
			c2.computercontrol(tails, knuckles);
			t = false;
			k = true;
			s = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player->active_character(sonic);
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
			tails->fly(lvl, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		}
		if (!mottobug->getDead())
		{
			mottobug->collision(player);
			mottobug->update(player, cell_size);
			mottobug->render(window);
		}
		else
			cout << "IDIEDDDD!!!!";

		if (!crab->getDead())
		{
			crab->collision(player);
			crab->update(player, cell_size);
			crab->render(window);
		}

		if (!beebot->getDead())
		{
			beebot->update(player, cell_size);
			beebot->render(window);
		}
		if (!bat->getDead())
		{
			bat->update(player, cell_size);
			bat->render(window);
		}

		player->gettingPowerUp();
		player->gettinghurt();
		for (int i = 0; i < ringCount; ++i) {
			if (ringArray[i]->getOn())
			{
				ringArray[i]->setScaleC(0.75f, 0.75f);
				ringArray[i]->update();
				ringArray[i]->collision(player);
				ringArray[i]->render(window);
			}
		}
		for (int i = 0; i < boastCount; ++i) {
			if (boastArray[i]->getOn())
			{
				boastArray[i]->setScaleC(0.75f, 0.75f);
				boastArray[i]->update();
				boastArray[i]->collision(player);
				boastArray[i]->render(window);
			}
		}
		for (int i = 0; i < lifeCount; ++i) {
			if (lifeArray[i]->getOn())
			{
				lifeArray[i]->setScaleC(0.75f, 0.75f);
				lifeArray[i]->update();
				lifeArray[i]->collision(player);
				lifeArray[i]->render(window);
			}
		}
		updateHUD(player);

		window.setView(window.getDefaultView()); // Switch to default view for HUD
		window.draw(scoreText);
		window.draw(livesText);
		window.draw(powerUpText);
		window.setView(view); // Switch back to game view

		window.setView(view);
		window.display();

	}
};
class Level3 :public  Levels
{
public:
	Level3(int screen_x, int screen_y) : Levels(screen_x, screen_y)
	{
		width = 300;
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};

		}

		level = 2;
		mottobug = new MottoBug(64 * 80, 64 * 8, 64 * 86, 64 * 8);
		mottobug->setScale(3.0f, 3.0f);
		crab = new CrabMeat(64 * 96, 64 * 9.6, 64 * 105, 64 * 9.6);
		crab->setScale(3.0f, 3.0f);
		beebot = new BeeBot(64 * 124, 64 * 4, 64 * 135, 64 * 4);
		beebot->setScale(3.0f, 3.0f);

		ringArray = new Rings * [200];
		boastArray = new Boast * [200];
		lifeArray = new Life * [200];


		//bg textures for level3 


		sf::Vector2f scaleFactorL = { 4.0f, 4.0f };
		lionT.loadFromFile("Data/level3Sprites/decor l3.png");
		lionsprite.setTexture(lionT);
		scaleFactorL.x = 4.0f;
		scaleFactorL.y = 4.0f;
		lionsprite.setScale(scaleFactorL);

		lionTRt.loadFromFile("Data/level3Sprites/l3 decor(2).png");
		lionspriteRt.setTexture(lionTRt);
		lionspriteRt.setScale(scaleFactorL);


		sf::Vector2f scaleFactorB = { 2.0f, 2.0f };
		brickTx4.loadFromFile("Data/decor/breakablewall.png");
		brickSp4.setTexture(brickTx4);
		scaleFactorB.x = 2.0f;
		scaleFactorB.y = 2.0f;
		brickSp4.setScale(scaleFactorB);

		crystaltex.loadFromFile("Data/crystal.png");
		crystalsp.setTexture(crystaltex);

		sf::Vector2f scaleFactor = { 1.0f, 1.0f };
		leafT.loadFromFile("Data/level2 FS/level (30).png");
		leafsprite.setTexture(leafT);
		scaleFactor.x = 1.0f;
		scaleFactor.y = 1.0f;
		leafsprite.setScale(scaleFactor);

		//Textures and sprites loading
		wallTex1.loadFromFile("Data/bg4.png");
		wallSprite1.setTexture(wallTex1);

		sf::Vector2f scaleFactorP = { 1.0f, 1.0f };
		brickTx1.loadFromFile("Data/level3Sprites/l3block (7).png");
		brickSp1.setTexture(brickTx1);
		scaleFactorP.x = 1.0f;
		scaleFactorP.y = 1.0f;
		brickSp1.setScale(scaleFactorP);

		sf::Vector2f scaleFactorI = { 1.0f, 1.0f };
		brickTx2.loadFromFile("Data/level3Sprites/l3block (5).png");
		brickSp2.setTexture(brickTx2);
		scaleFactorI.x = 1.0f;
		scaleFactorI.y = 1.0f;
		brickSp2.setScale(scaleFactorI);

		brickTx3.loadFromFile("Data/level3Sprites/l3block (2).png");
		brickSp3.setTexture(brickTx3);
		brickSp3.setScale(scaleFactorI);

		spikeTx.loadFromFile("Data/spike.png");
		spikeSp.setTexture(spikeTx);
	}
	~Level3()
	{
		freeRings();
		freeBoast();
		for (int i = 0; i < lifeCount; ++i) {
			delete lifeArray[i];
		}
		delete[] lifeArray;
		lifeArray = nullptr;
		for (int i = 0; i < height; i++)
		{
			delete[] lvl[i];
		}
		delete[] lvl;
		lifeCount = 0;
	}
	void initialization()
	{
		obj_ring.initializeGrid(lvl, height, width, level);
		obj_ring.placeOnGrid(lvl, 14, 300, ringArray, ringCount);
		obj_boast.initializeGrid(lvl, height, width, level);
		obj_boast.placeOnGrid(lvl, 14, 300, boastArray, boastCount);
		obj_life.initializeGrid(lvl, height, width, level);
		obj_life.placeOnGrid(lvl, 14, 300, lifeArray, lifeCount);
		for (int j = 0; j < width; j++)
		{
			lvl[height - 3][j] = 'w';
			lvl[height - 2][j] = 'q';
			lvl[height - 1][j] = 'q';
			for (int j = 5; j < 15; j++)
				lvl[height - 7][j] = 'j';

			lvl[0][10] = 'O';
			lvl[0][20] = 'o';
			for (int j = 55; j < 65; j++)
				lvl[height - 4][j] = 'p';

			for (int i = 0; i < 3; i++)
				lvl[height - 4 - i][75] = 'w';

			for (int j = 78; j < 88; j++)
				lvl[height - 8][j] = 'j';

			lvl[0][80] = 'o';
			lvl[0][83] = 'O';
			for (int i = 0; i < 6; i++)
				lvl[height - 4 - i][120] = 'w';
			for (int j = 123; j < 130; j++)
				lvl[height - 7][j] = 'j';
			lvl[height - 11][125] = 'j';
			for (int i = 4; i < 10; i++)
			{
				lvl[i][175] = 'w';
				lvl[i][180] = 'w';
			}
			for (int j = 185; j < 195; j++)
				lvl[height - 6][j] = 'j';

			lvl[height - 8][190] = 'p';
			for (int j = 255; j < 260; j++)
				lvl[height - 6][j] = 'j';
			for (int j = 265; j < 270; j++)
				lvl[height - 8][j] = 'j';
			for (int j = 275; j < 280; j++)
				lvl[height - 10][j] = 'j';

			lvl[height - 7][285] = 'p';
			lvl[0][260] = 'O';
			lvl[0][280] = 'o';


		}
	}


};
class Level4 :public  Levels
{
 
	//bool eggdead;
public:
	Level4(int screen_x, int screen_y) : Levels(screen_x, screen_y)
	{

		width = 300;
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};

		}

		level = 4;
		/*mottobug = new MottoBug(64 * 80, 64 * 8, 64 * 86, 64 * 8);
		mottobug->setScale(3.0f, 3.0f);
		crab = new CrabMeat(64 * 96, 64 * 9.6, 64 * 105, 64 * 9.6);
		crab->setScale(3.0f, 3.0f);
		beebot = new BeeBot(64 * 124, 64 * 4, 64 * 135, 64 * 4);
		beebot->setScale(3.0f, 3.0f);*/
		eggstinger = new EggStinger(64 * 0, 64 * 0, 64 * 12 + 400, 64 * 0, lvl);
		eggstinger->setScale(3.0f, 3.0f);

		ringArray = new Rings * [200];
		boastArray = new Boast * [200];
		lifeArray = new Life * [200];


		//bg textures for level3 


		sf::Vector2f scaleFactorL = { 4.0f, 4.0f };
		lionT.loadFromFile("Data/level3Sprites/decor l3.png");
		lionsprite.setTexture(lionT);
		scaleFactorL.x = 4.0f;
		scaleFactorL.y = 4.0f;
		lionsprite.setScale(scaleFactorL);

		lionTRt.loadFromFile("Data/level3Sprites/l3 decor(2).png");
		lionspriteRt.setTexture(lionTRt);
		lionspriteRt.setScale(scaleFactorL);


		sf::Vector2f scaleFactorB = { 2.0f, 2.0f };
		brickTx4.loadFromFile("Data/decor/breakablewall.png");
		brickSp4.setTexture(brickTx4);
		scaleFactorB.x = 2.0f;
		scaleFactorB.y = 2.0f;
		brickSp4.setScale(scaleFactorB);

		crystaltex.loadFromFile("Data/crystal.png");
		crystalsp.setTexture(crystaltex);

		sf::Vector2f scaleFactor = { 1.0f, 1.0f };
		leafT.loadFromFile("Data/level2 FS/level (30).png");
		leafsprite.setTexture(leafT);
		scaleFactor.x = 1.0f;
		scaleFactor.y = 1.0f;
		leafsprite.setScale(scaleFactor);

		//Textures and sprites loading
		sf::Vector2f scaleFactorW = { 10.0f, 10.0f };
		wallTex1.loadFromFile("Data/level4 bg.png");
		wallSprite1.setTexture(wallTex1);
		scaleFactorW.x = 4.0f;
		scaleFactorW.y = 4.0f;
		wallSprite1.setScale(scaleFactorW);


		sf::Vector2f scaleFactorP = { 1.0f, 1.0f };
		brickTx1.loadFromFile("Data/level3 brick.png");
		brickSp1.setTexture(brickTx1);
		scaleFactorP.x = 2.0f;
		scaleFactorP.y = 2.0f;
		brickSp1.setScale(scaleFactorP);

		sf::Vector2f scaleFactorI = { 1.0f, 1.0f };
		brickTx2.loadFromFile("Data/level3Sprites/l3block (5).png");
		brickSp2.setTexture(brickTx2);
		scaleFactorI.x = 1.0f;
		scaleFactorI.y = 1.0f;
		brickSp2.setScale(scaleFactorI);

		brickTx3.loadFromFile("Data/level3Sprites/l3block (2).png");
		brickSp3.setTexture(brickTx3);
		brickSp3.setScale(scaleFactorI);

		/*spikeTx.loadFromFile("Data/spike.png");
		spikeSp.setTexture(spikeTx);*/
	}
	~Level4()
	{
		freeRings();
		freeBoast();
		for (int i = 0; i < lifeCount; ++i) {
			delete lifeArray[i];
		}
		delete[] lifeArray;
		for (int i = 0; i < height; i++)
		{
			delete[] lvl[i];
		}
		delete[] lvl;
		lifeArray = nullptr;
		lifeCount = 0;
	}
	void initialization()
	{
		obj_ring.initializeGrid(lvl, height, width, level);
		obj_ring.placeOnGrid(lvl, 14, 300, ringArray, ringCount);
		obj_boast.initializeGrid(lvl, height, width, level);
		obj_boast.placeOnGrid(lvl, 14, 300, boastArray, boastCount);
		obj_life.initializeGrid(lvl, height, width, level);
		obj_life.placeOnGrid(lvl, 14, 300, lifeArray, lifeCount);
		for (int j = 0; j < width; j++)
		{
			lvl[height - 3][j] = 'w';
			/*lvl[height - 2][j] = 'w';
			lvl[height - 1][j] = 'w';*/
			//lvl[height ][j] = 'w';
			for (int i = 0; i < 3; i++)
			{
				lvl[4][7 + i] = 'j';
				lvl[6][11 + i] = 'j';
				lvl[8][15 + i] = 'j';

				//lvl[][7 + i] = 'w';
			}
		}
	}

	void runlevel(RenderWindow& window, bool toggle[], bool boggle[], Player* player, Computer_Controlled& c1, Computer_Controlled& c2, Knuckles* knuckles, Sonic* sonic, Tails* tails, View& view, FloatRect& cameraview)
	{
		if (level == 1 && lvlMus.getStatus() != SoundSource::Playing)
		{// if current level is 1 and music is not playing then tis loop would play music
			if (!lvlMus.openFromFile("Data/labrynth.ogg"))
			{
				std::cerr << "Failed to load level 1 music!" << std::endl;
			}
			lvlMus.setVolume(30);
			lvlMus.setLoop(true);
			lvlMus.play();
		}
		///// PARTTT OF ANIMATIONSSSSS ////////

		player->apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		c1.apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		c2.apply_gravity(lvl, offset_y, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		window.clear();
		//sf::Vector2f viewCenter = view.getCenter();
		/*std::cout << "View Center: (" << viewCenter.x << ", " << viewCenter.y << ")\n";
		std::cout << "Player Position: (" << player->getX() << ", " << player->getY() << ")\n";*/
		display_level(window);
		//moveView(window, player->getX(), player->getY(), view, cameraview);
		player->animate(toggle, boggle);
		c1.animate(toggle, boggle);
		c2.animate(toggle, boggle);
		player->draw(window);
		c1.draw(window);
		c2.draw(window);
		player->move(lvl, cell_size, width, offset_y, hit_box_factor_x, hit_box_factor_y, Pheight, Pwidth);
		c1.update(lvl, cell_size, width, height);
		c2.update(lvl, cell_size, width, height);

		//sf::View view = window.getView();
		//view.setCenter(sf::Vector2f(500.f, 300.f));  // Force view to center on (500, 300)

		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			player->active_character(tails);
			c1.computercontrol(sonic, tails);
			c2.computercontrol(knuckles, sonic);
			t = true;
			k = false;
			s = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::K))
		{
			player->active_character(knuckles);
			c1.computercontrol(sonic, tails);
			c2.computercontrol(tails, knuckles);
			t = false;
			k = true;
			s = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player->active_character(sonic);
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
			tails->fly(lvl, hit_box_factor_x, hit_box_factor_y, cell_size, Pheight, Pwidth);
		}
		/*if (!mottobug->getDead())
		{
			mottobug->collision(player);
			mottobug->update(player, cell_size);
			mottobug->render(window);
		}
		else
			cout << "IDIEDDDD!!!!";

		if (!crab->getDead())
		{
			crab->collision(player);
			crab->update(player, cell_size);
			crab->render(window);
		}

		if (!beebot->getDead())
		{
			beebot->update(player, cell_size);
			beebot->render(window);
		}*/
		if (!eggstinger->getDead())
		{
			eggstinger->update(player, cell_size);
			eggstinger->collision(player);
			eggstinger->render(window);
		}

		player->gettingPowerUp();
		player->gettinghurt();
		for (int i = 0; i < ringCount; ++i) {
			if (ringArray[i]->getOn())
			{
				ringArray[i]->setScaleC(0.75f, 0.75f);
				ringArray[i]->update();
				ringArray[i]->collision(player);
				ringArray[i]->render(window);
			}
		}
		for (int i = 0; i < boastCount; ++i) {
			if (boastArray[i]->getOn())
			{
				boastArray[i]->setScaleC(0.75f, 0.75f);
				boastArray[i]->update();
				boastArray[i]->collision(player);
				boastArray[i]->render(window);
			}
		}
		for (int i = 0; i < lifeCount; ++i) {
			if (lifeArray[i]->getOn())
			{
				lifeArray[i]->setScaleC(0.75f, 0.75f);
				lifeArray[i]->update();
				lifeArray[i]->collision(player);
				lifeArray[i]->render(window);
			}
		}
		window.setView(view);
		window.display();

	}

};