#include <iostream>
#include <fstream>
#include <cstdlib> //for rand func
#include <ctime> //for srand func
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
int h;
using namespace sf;
using namespace std;

int screen_x = 1200;
int screen_y = 900;

// prototypes 
void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth);

void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y);

void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size, Sprite& brickSp1, Sprite& brickSp2, Sprite& brickSp3, Sprite spikeSp);

void movePlayer(float& player_x);

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
		for (int k = 0;k < 3;k++)
		{
			lvl[height - 4 - k][14] = 'w';
		}
		//adding obstacles
		//mainly blocks
		//in the array the first element is the y axis
		// the second element is the z axis
		for (int k = 0;k < 3;k++)
		{
			lvl[height - 6][16 + k] = 'w';
			lvl[1][16] = 'w';
			lvl[1][16+1] = 'w';
			lvl[2][16+1] = 'w';
		}
		for (int k = 0;k < 3;k++)
		{
			lvl[height - 6][20 + k] = 'w';
			lvl[1][16 + 1] = 'w';
			lvl[2][16 + 1] = 'w';
			lvl[1][16 + 1] = 'w';

		}

		
		for (int k = 0;k < 3;k++)
		{
			lvl[height - 6][25 + k] = 'w';
			lvl[1][20 ] = 'w';
			lvl[1][20 + 1] = 'w';
			lvl[2][20 + 1] = 'w';
			lvl[1][20 + 2] = 'w';
			lvl[10][19+k] = 'p';

		}
		for (int k = 0;k < 3;k++)
		{
			lvl[height - 6][31 + k] = 'w';


		}
		//knuckles region
		//wall breaking
		for (int k = 0;k < 11;k++)
		{
			lvl[k][34 ] = 'w';
			lvl[k][35] = 'w';
			lvl[k][36] = 'w';
			
			lvl[k][42] = 'w';
			
			for (int i = 0;i < 5;i++)
			{
				lvl[1][42] = 'w';
				lvl[1][37 + i] = 'w';
				lvl[2][37 + i] = 'w';
				
					lvl[height - 4][36] = 'w';
					if (i < 5)
					{//spikes in the region
						lvl[height - 4][37 + i] = 'p';
					}

				lvl[height-5][36] = 'w';
				
				
					lvl[height - 7][37 + i] = 'w';
				
				lvl[height - 8][39] = 'p';
				if (i < 4)
				{
					lvl[height - 7][42 + i] = 'w';

					lvl[height - 6][42 + i ] = 'w';
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
		for (int i = 0;i < 3;i++)
		{
			lvl[height - 6][51 + i] = 'w';
			lvl[height - 8][55 + i] = 'w';
			lvl[height - 10][59 + i] = 'w';
			lvl[6][90 + i] = 'w';
		}
		//motto bug enemy zone
		for (int i = 0;i < 9;i++)
		{
			lvl[height - 2][51 + i] = ' ';
			lvl[height - 1][51 + i] = ' ';
			//lvl[height-3 ][51 + i] = ' ';
		}

		lvl[height - 1][j] = 'q';
		lvl[height - 3][j] = 'w';
		lvl[height - 2][j] = 'q';
		for (int i = 0;i < 20;i++)
		{
			lvl[1][68 + i] = 'q';
			lvl[2][68 + i] = 'q';
		}
		for (int k = 0;k < 2;k++)
		{
			lvl[height - 8][68 + k] = 'w';
			lvl[height - 8][73 + k] = 'w';
			lvl[height - 8][81 + k] = 'w';
			lvl[height - 8][86 + k] = 'w';
		}
		for (int i = 0;i < 11;i++)
		{
			lvl[i][89] = 'q';
			lvl[i][90] = 'q';
			lvl[i][88] = 'q';
		}
		//all the pits logic here
		for (int i = 0;i < 15;i++)
		{
			lvl[height - 2][91 + i] = ' ';
			lvl[height - 1][91 + i] = ' ';
			//lvl[height-3 ][51 + i] = ' ';
			//lvl[height - 2][116 + i] = ' ';
			//lvl[height - 2][172 + i] = ' ';
			////lvl[height - 3][172 + i] = ' ';
		}

		//stairs for mid level mini boss fight
		for (int i = 0;i < 7;i++)
		{
			lvl[height - 4][107 + i] = 'w';
			if(i<6)
			lvl[height - 5][108 + i] = 'w';
			if(i<5)
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
			lvl[height - 2][131 + i] = ' ';
		/*	lvl[height - 2][187 + i] = ' ';
			lvl[height - 1][187 + i] = ' ';*/
		}
		//wall breaking pt 2
		for (int k = 0;k < 11;k++)
		{
			lvl[k][139] = 'w';
			lvl[k][140] = 'w';
			lvl[k][141] = 'w';

			lvl[k][147] = 'w';
			//42=147
			for (int i = 0;i < 5;i++)
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
			for (int i = 0;i < 8;i++)
			{
				lvl[4][159+i] = 'q';
				lvl[5][159+i] = 'q';
			}
			lvl[6][158] = 'q';
			lvl[6][167] = 'q';
			


		}
		

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

	LstillTex.loadFromFile("Data/0right_still.png");
	LstillSprite.setTexture(LstillTex);
	LstillSprite.setScale(scale_x, scale_y);

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

		player_gravity(lvl, offset_y, velocityY, onGround, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, player_x, player_y, cell_size, Pheight, Pwidth);

		window.clear();

		display_level(window, height, width, lvl, wallSprite1, cell_size, brickSp1, brickSp2, brickSp3, spikeSp);
		moveView(view, player_x, player_y, cameraview);
		draw_player(window, LstillSprite, player_x, player_y);
		movePlayer(player_x);
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
void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, const int cell_size, Sprite& brickSp1, Sprite& brickSp2, Sprite& brickSp3, Sprite spikeSp)
{
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			if (lvl[i][j] == 's')
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
void movePlayer(float& player_x)
{
	Keyboard key;
	if (key.isKeyPressed(key.Left))
	{
		player_x -= 25;
	}
	else if (key.isKeyPressed(key.Right))
	{
		player_x += 25;
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
		/*if (player_y < cameraview.top)
			view.move(0, player_y - cameraview.top);*/
		if (player_y > cameraview.top + cameraview.height)
			view.move(0, player_y - (cameraview.top + cameraview.height));
	}
}