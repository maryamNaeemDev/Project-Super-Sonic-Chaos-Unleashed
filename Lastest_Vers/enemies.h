#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

#include"character.h"
using namespace std;

class Enemies {
protected:
	//int hp;
	//int hits;
	int s_position_x, s_position_y;
	int f_position_x, f_position_y;
	bool dead=false;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f scaleFactor = { 1.0f, 1.0f };
	sf::SoundBuffer hurtBuffer;
	sf::Sound hurtSound;
protected://since so many enemies are sharing the same func
	//virtual void loadSprite(const std::string& path) = 0;
	static const int IDLE_LEFT = 0;
	static const int MOVING_LEFT = 1;
	static const int IDLE_RIGHT = 2;
	static const int DOWN = 2;
	static const int UP = 0;
	static const int MOVING_RIGHT = 3;

	int currentAnimationState;
public:
	virtual void update(Player* player, int cellSize) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual bool collision(Player* players) = 0;

	virtual void life() = 0;
	virtual int getHp() const = 0;
	virtual int getHits() const = 0;

	virtual int getStartX() const = 0;
	virtual int getStartY() const = 0;
	virtual int getFinalX() const = 0;
	virtual int getFinalY() const = 0;
	//for the position of the sprite
	virtual void setPosition(int x, int y) = 0;
	//for the size of the sprite
	//virtual void setScale(float scaleX, float scaleY);
	//enemies animations 
	virtual void playIdleLeftAnimation() {}
	virtual void playMovingLeftAnimation() {}
	virtual void playIdleRightAnimation() {}
	virtual void playMovingRightAnimation() {}

	bool getDead() { return dead; }
	void setDead(bool b) { dead = b; }


	virtual ~Enemies() {}
};
//void Enemies::setScale(float scaleX, float scaleY) {
//	scaleFactor.x = scaleX;
//	scaleFactor.y = scaleY;
//	sprite.setScale(scaleFactor);
//}


class Crawl : public Enemies {
public:
	virtual void crawlBehavior() = 0;
};

class Fly : public Enemies {
public:
	virtual void flyBehavior() = 0;
};

class MottoBug : public Crawl
{
private:
	sf::Texture textureLeft;
	sf::Sprite spriteLeft;
	sf::Texture textureLeft1;
	sf::Sprite spriteLeft1;
	sf::Texture textureRight;
	sf::Sprite spriteRight;
	sf::Texture textureRight1;
	sf::Sprite spriteRight1;
	int hp = 2;
	int hits = 0;

	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;

	bool movingRight = true;
	float speed = 2.0f;
	sf::Clock animationClock;
	sf::Time frameTime = sf::seconds(0.5f);
	bool currentLeftFrame = true;
	bool currentRightFrame = true;
public:
	MottoBug(int startX, int startY, int endX, int endY) {
		s_position_x = startX;
		s_position_y = startY;
		f_position_x = endX;
		f_position_y = endY;
		currentAnimationState = MOVING_RIGHT;


		// Load all textures in constructor
		if (!textureLeft.loadFromFile("Data/Enemies/MBF/mottobug 1.png")) {
			std::cerr << "Error loading motto bug left frame 1 texture!" << std::endl;
		}
		spriteLeft.setTexture(textureLeft);

		if (!textureLeft1.loadFromFile("Data/Enemies/MBF/mottobug 7.png")) {
			std::cerr << "Error loading motto bug left frame 2 texture!" << std::endl;
		}
		spriteLeft1.setTexture(textureLeft1);

		if (!textureRight.loadFromFile("Data/Enemies/MBF/mottobug 14(2).png")) {
			std::cerr << "Error loading motto bug right frame 1 texture!" << std::endl;
		}
		spriteRight.setTexture(textureRight);

		if (!textureRight1.loadFromFile("Data/Enemies/MBF/mottobug 7(2).png")) {
			std::cerr << "Error loading motto bug right frame 2 texture!" << std::endl;
		}
		spriteRight1.setTexture(textureRight1);

		// Set initial positions and scale
		setPosition(startX, startY);


		if (!hurtBuffer.loadFromFile("Data/Hurt.ogg")) {
			std::cerr << "Error loading jump sound!" << std::endl;
		}
		hurtSound.setBuffer(hurtBuffer);
		hurtSound.setVolume(30);
		animate();
	}



	void update(Player* player, int cellSize) override {
		if (movingRight) {
			s_position_x += speed;
			if (s_position_x >= f_position_x) movingRight = false;
			currentAnimationState = MOVING_RIGHT;
		}
		else {
			s_position_x -= speed;
			if (s_position_x <= f_position_x - 1200) movingRight = true;
			currentAnimationState = MOVING_LEFT;
		}
		animate();
	}

	void render(sf::RenderWindow& window) override {
		if (movingRight) {

			if (currentRightFrame) {
				window.draw(spriteRight);
			}
			else {
				window.draw(spriteRight1);
			}
		}
		else {
			if (currentLeftFrame) {
				window.draw(spriteLeft);
			}
			else {
				window.draw(spriteLeft1);
			}

		}
	}


	bool collision(Player* players) override {
		sf::FloatRect bugBounds;
		if (movingRight) {
			bugBounds = currentRightFrame ? spriteRight.getGlobalBounds() : spriteRight1.getGlobalBounds();
		}
		else {
			bugBounds = currentLeftFrame ? spriteLeft.getGlobalBounds() : spriteLeft1.getGlobalBounds();
		}
		sf::FloatRect playerBounds = players->getSprite().getGlobalBounds();
		if (bugBounds.intersects(playerBounds)) {
			if (players->getIsJumping())
			{
				dead = true;
				return true;
			}
			else
			{
				cout << "OUCHHHH THAT HURTTTTTT" << endl;
				hurtSound.play();
				players->setHurtRight(movingRight);
				players->setHurt(true);

				return true;
			}
		}
		return false;
	}

	void life() override {}

	int getHp() const override { return hp; }
	int getHits() const override { return hits; }

	int getStartX() const override { return s_position_x; }
	int getStartY() const override { return s_position_y; }
	int getFinalX() const override { return f_position_x; }
	int getFinalY() const override { return f_position_y; }

	void setPosition(int x, int y) override {
		s_position_x = x;
		s_position_y = y;

		spriteLeft.setPosition(x, y);
		spriteLeft1.setPosition(x, y);
		spriteRight.setPosition(x, y);
		spriteRight1.setPosition(x, y);
	}

	void crawlBehavior() override {
		// Can be left empty unless needed
	}
	void setScale(float scaleX, float scaleY) {
		scaleFactor.x = scaleX;
		scaleFactor.y = scaleY;
		spriteLeft.setScale(scaleFactor);
		spriteRight.setScale(scaleFactor);
		spriteLeft1.setScale(scaleFactor);
		spriteRight1.setScale(scaleFactor);

	}
	void animate()
	{
		switch (currentAnimationState)
		{
		case MOVING_LEFT:

			if (animationClock.getElapsedTime() >= frameTime) {
				currentLeftFrame = !currentLeftFrame;
				animationClock.restart();
			}
			if (currentLeftFrame) {
				
				spriteLeft.setPosition(s_position_x, s_position_y);
				spriteLeft.setScale(scaleFactor);
			}
			else {
				spriteLeft1.setPosition(s_position_x, s_position_y);
				spriteLeft1.setScale(scaleFactor);
			}
			break;

		case MOVING_RIGHT:
		{
			if (animationClock.getElapsedTime() >= frameTime)
			{
				currentRightFrame = !currentRightFrame;
				animationClock.restart();
			}
			if (currentRightFrame) {
				spriteRight.setPosition(s_position_x, s_position_y);
				spriteRight.setScale(scaleFactor);
			}
			else
			{
				spriteRight1.setPosition(s_position_x, s_position_y);
				spriteRight1.setScale(scaleFactor);
			}
		}

		}

	}
};



class CrabMeat :public Crawl
{

	sf::Texture textureLeftFrame[3];
	sf::Sprite spriteLeftFrame[3];
	sf::Texture textureRightFrame[3];
	sf::Sprite spriteRightFrame[3];
	int hp = 2;
	int hits = 0;
	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;
	bool movingRight = true;
	float speed = 4.0f;
	sf::Clock animationClock;
	sf::Time frameTime = sf::seconds(0.15f); // Adjust frame time as needed
	int currentLeftFrameIndex = 0; // Index to track the current left animation frame
	int currentRightFrameIndex = 0;
public:
	CrabMeat(int startX, int startY, int endX, int endY) :
		s_position_x(startX), s_position_y(startY), f_position_x(endX), f_position_y(endY)
	{
		currentAnimationState = MOVING_RIGHT;


		// Load all left frame textures
		if (!textureLeftFrame[0].loadFromFile("Data/CMF/crab meat 2.png")) {
			std::cerr << "Error loading crab meat left frame 1 texture!" << std::endl;
		}
		spriteLeftFrame[0].setTexture(textureLeftFrame[0]);

		if (!textureLeftFrame[1].loadFromFile("Data/CMF/crab meat 10.png")) {
			std::cerr << "Error loading crab meat left frame 2 texture!" << std::endl;
		}
		spriteLeftFrame[1].setTexture(textureLeftFrame[1]);

		if (!textureLeftFrame[2].loadFromFile("Data/CMF/crab meat 5.png")) {
			std::cerr << "Error loading crab meat left frame 3 texture!" << std::endl;
		}
		spriteLeftFrame[2].setTexture(textureLeftFrame[2]);

		// Load all right frame textures
		if (!textureRightFrame[0].loadFromFile("Data/CMF/crab meat 7.png")) {
			std::cerr << "Error loading crab meat right frame 1 texture!" << std::endl;
		}
		spriteRightFrame[0].setTexture(textureRightFrame[0]);

		if (!textureRightFrame[1].loadFromFile("Data/CMF/crab meat 9.png")) {
			std::cerr << "Error loading crab meat right frame 2 texture!" << std::endl;
		}
		spriteRightFrame[1].setTexture(textureRightFrame[1]);

		if (!textureRightFrame[2].loadFromFile("Data/CMF/crab meat 6.png")) {
			std::cerr << "Error loading crab meat right frame 3 texture!" << std::endl;
		}
		spriteRightFrame[2].setTexture(textureRightFrame[2]);

		// Set initial positions
		setPosition(startX, startY);




		animate(); // Load initial sprite
		if (!hurtBuffer.loadFromFile("Data/Hurt.ogg")) {
			std::cerr << "Error loading jump sound!" << std::endl;
		}
		hurtSound.setBuffer(hurtBuffer);
		hurtSound.setVolume(30);

	}

	void update(Player* player, int cellSize) override {
		if (movingRight) {
			s_position_x += speed;
			if (s_position_x >= f_position_x) movingRight = false;
			currentAnimationState = MOVING_RIGHT;
		}
		else {
			s_position_x -= speed;
			if (s_position_x <= f_position_x - 1200) movingRight = true;
			currentAnimationState = MOVING_LEFT;
		}
		animate();
	}

	void render(sf::RenderWindow& window) override {
		if (movingRight) {
			window.draw(spriteRightFrame[currentRightFrameIndex]);
		}
		else {
			window.draw(spriteLeftFrame[currentLeftFrameIndex]);
		}
	}

	bool collision(Player* players) override {
		sf::FloatRect crabBounds;
		if (movingRight) {
			crabBounds = spriteRightFrame[currentRightFrameIndex].getGlobalBounds();
		}
		else {
			crabBounds = spriteLeftFrame[currentLeftFrameIndex].getGlobalBounds();
		}
		sf::FloatRect playerBounds = players->getSprite().getGlobalBounds();
		if (crabBounds.intersects(playerBounds)) {
			if (players->getIsJumping())
			{
				dead = true;
				return true;
			}
			else
			{
				cout << "OUCHHHH THAT HURTTTTTT" << endl;
				hurtSound.play();
				players->setHurtRight(movingRight);
				players->setHurt(true);

				return true;
			}

			cout << "OUCHHHH THAT HURTTTTTT" << endl;
			
		}
		return false;
	}

	void life() override {}

	int getHp() const override { return hp; }
	int getHits() const override { return hits; }

	int getStartX() const override { return s_position_x; }
	int getStartY() const override { return s_position_y; }
	int getFinalX() const override { return f_position_x; }
	int getFinalY() const override { return f_position_y; }

	void setPosition(int x, int y) override {
		s_position_x = x;
		s_position_y = y;
		for (int i = 0; i < 3; ++i) {
			spriteLeftFrame[i].setPosition(x, y);
			spriteRightFrame[i].setPosition(x, y);
		}
	}

	void crawlBehavior() override {}

	void setScale(float scaleX, float scaleY) {
		scaleFactor.x = scaleX;
		scaleFactor.y = scaleY;
		for (int i = 0; i < 3; ++i) {
			spriteLeftFrame[i].setScale(scaleFactor);
			spriteRightFrame[i].setScale(scaleFactor);
		}
	}

	void animate() {
		if (animationClock.getElapsedTime() >= frameTime) {
			animationClock.restart();
			if (currentAnimationState == MOVING_LEFT) {
				currentLeftFrameIndex = (currentLeftFrameIndex + 1) % 3;
				//std::cout << "Current left frame index: " << currentLeftFrameIndex << std::endl;
			}
			else if (currentAnimationState == MOVING_RIGHT) {
				currentRightFrameIndex = (currentRightFrameIndex + 1) % 3;
				//std::cout << "Current right frame index: " << currentRightFrameIndex << std::endl;
			}
		}

		switch (currentAnimationState) {
		case MOVING_LEFT:
		{
			spriteLeftFrame[currentLeftFrameIndex].setPosition(s_position_x, s_position_y);
			spriteLeftFrame[currentLeftFrameIndex].setScale(scaleFactor);
			break;
		}
		case MOVING_RIGHT:
		{
			spriteRightFrame[currentRightFrameIndex].setPosition(s_position_x, s_position_y);
			spriteRightFrame[currentRightFrameIndex].setScale(scaleFactor);
			break;
		}
		case IDLE_LEFT:
			// Load idle left sprite (you might want to make this multi-frame as well)
			break;
		case IDLE_RIGHT:
			// Load idle right sprite (you might want to make this multi-frame as well)
			break;
		}
	}
};
class BeeBot :public Fly
{
	sf::Texture textureLeftFrame[3];
	sf::Sprite spriteLeftFrame[3];
	sf::Texture textureRightFrame[3];
	sf::Sprite spriteRightFrame[3];
	int hp = 2;
	int hits = 0;
	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;
	bool movingRight = true;
	float speed = 4.0f;
	sf::Clock animationClock;
	sf::Time frameTime = sf::seconds(0.15f); // Adjust frame time as needed
	int currentLeftFrameIndex = 0; // Index to track the current left animation frame
	int currentRightFrameIndex = 0;
public:
	BeeBot(int startX, int startY, int endX, int endY) :
		s_position_x(startX), s_position_y(startY), f_position_x(endX), f_position_y(endY)
	{
		currentAnimationState = MOVING_RIGHT;


		// Load all left frame textures
		if (!textureLeftFrame[0].loadFromFile("Data/BBF/bee 1.png")) {
			std::cerr << "Error loading bee left frame 1 texture!" << std::endl;
		}
		spriteLeftFrame[0].setTexture(textureLeftFrame[0]);

		if (!textureLeftFrame[1].loadFromFile("Data/BBF/bee2.png")) {
			std::cerr << "Error loading bee left frame 2 texture!" << std::endl;
		}
		spriteLeftFrame[1].setTexture(textureLeftFrame[1]);

		if (!textureLeftFrame[2].loadFromFile("Data/BBF/bee3.png")) {
			std::cerr << "Error loading bee left frame 3 texture!" << std::endl;
		}
		spriteLeftFrame[2].setTexture(textureLeftFrame[2]);

		// Load all right frame textures
		if (!textureRightFrame[0].loadFromFile("Data/BBF/bee 1(rt).png")) {
			std::cerr << "Error loading bee right frame 1 texture!" << std::endl;
		}
		spriteRightFrame[0].setTexture(textureRightFrame[0]);

		if (!textureRightFrame[1].loadFromFile("Data/BBF/bee2(rt).png")) {
			std::cerr << "Error loading bee right frame 2 texture!" << std::endl;
		}
		spriteRightFrame[1].setTexture(textureRightFrame[1]);

		if (!textureRightFrame[2].loadFromFile("Data/BBF/bee3(rt).png")) {
			std::cerr << "Error loading bee right frame 3 texture!" << std::endl;
		}
		spriteRightFrame[2].setTexture(textureRightFrame[2]);

		// Set initial positions
		setPosition(startX, startY);


		animate(); // Load initial sprite
		if (!hurtBuffer.loadFromFile("Data/Hurt.ogg")) {
			std::cerr << "Error loading jump sound!" << std::endl;
		}
		hurtSound.setBuffer(hurtBuffer);
		hurtSound.setVolume(30);
	}

	void update(Player* player, int cellSize) override {
		if (movingRight) {
			s_position_x += speed;
			if (s_position_x >= f_position_x) movingRight = false;
			currentAnimationState = MOVING_RIGHT;
		}
		else {
			s_position_x -= speed;
			if (s_position_x <= f_position_x - 1200) movingRight = true;
			currentAnimationState = MOVING_LEFT;
		}
		animate();
	}

	void render(sf::RenderWindow& window) override {
		if (movingRight) {
			window.draw(spriteRightFrame[currentRightFrameIndex]);
		}
		else {
			window.draw(spriteLeftFrame[currentLeftFrameIndex]);
		}
	}

	bool collision(Player* players) override {
		return false;
	}

	void life() override {}

	int getHp() const override { return hp; }
	int getHits() const override { return hits; }

	int getStartX() const override { return s_position_x; }
	int getStartY() const override { return s_position_y; }
	int getFinalX() const override { return f_position_x; }
	int getFinalY() const override { return f_position_y; }

	void setPosition(int x, int y) override {
		s_position_x = x;
		s_position_y = y;
		for (int i = 0; i < 3; ++i) {
			spriteLeftFrame[i].setPosition(x, y);
			spriteRightFrame[i].setPosition(x, y);
		}
	}

	void flyBehavior() override {}

	void setScale(float scaleX, float scaleY) {
		scaleFactor.x = scaleX;
		scaleFactor.y = scaleY;
		for (int i = 0; i < 3; ++i) {
			spriteLeftFrame[i].setScale(scaleFactor);
			spriteRightFrame[i].setScale(scaleFactor);
		}
	}

	void animate() {
		if (animationClock.getElapsedTime() >= frameTime) {
			animationClock.restart();
			if (currentAnimationState == MOVING_LEFT) {
				currentLeftFrameIndex = (currentLeftFrameIndex + 1) % 3;
				std::cout << "Current left frame index: " << currentLeftFrameIndex << std::endl;
			}
			else if (currentAnimationState == MOVING_RIGHT) {
				currentRightFrameIndex = (currentRightFrameIndex + 1) % 3;
				std::cout << "Current right frame index: " << currentRightFrameIndex << std::endl;
			}
		}

		switch (currentAnimationState) {
		case MOVING_LEFT:
		{
			spriteLeftFrame[currentLeftFrameIndex].setPosition(s_position_x, s_position_y);
			spriteLeftFrame[currentLeftFrameIndex].setScale(scaleFactor);
			break;
		}
		case MOVING_RIGHT:
		{
			spriteRightFrame[currentRightFrameIndex].setPosition(s_position_x, s_position_y);
			spriteRightFrame[currentRightFrameIndex].setScale(scaleFactor);
			break;
		}
		case IDLE_LEFT:
			// Load idle left sprite (you might want to make this multi-frame as well)
			break;
		case IDLE_RIGHT:
			// Load idle right sprite (you might want to make this multi-frame as well)
			break;
		}
	}
};
class BatBrain :public Fly
{
	sf::Texture BBTLeftFrame[10];
	sf::Sprite BBSLeftFrame[10];
	sf::Texture BBTRightFrame[10];
	sf::Sprite BBSRightFrame[10];

	int hp = 4;
	int hits = 0;
	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;

	bool  movingright = true;
	float speed = 4.0f;

	sf::Clock AnimationClock;
	sf::Time timeperframe = sf::seconds(0.1);
	int Lf = 0;
	int Lr = 0;

public:
	BatBrain(int x1, int y1, int x2, int y2)
	{
		s_position_x = x1;
		s_position_y = y1;
		f_position_x = x2;
		f_position_y = y2;

		// Load all left frame textures
		if (!BBTLeftFrame[0].loadFromFile("Data/BatF/bb still.png") ||
			!BBTLeftFrame[1].loadFromFile("Data/BatF/Bat left1.png") ||
			!BBTLeftFrame[2].loadFromFile("Data/BatF/bb left2.png") ||
			!BBTLeftFrame[3].loadFromFile("Data/BatF/bb left3.png") ||
			!BBTLeftFrame[4].loadFromFile("Data/BatF/bb left4.png") ||
			!BBTLeftFrame[5].loadFromFile("Data/BatF/bb left5.png") ||
			!BBTLeftFrame[6].loadFromFile("Data/BatF/bb left6.png") ||
			!BBTLeftFrame[7].loadFromFile("Data/BatF/bb left7.png") ||
			!BBTLeftFrame[8].loadFromFile("Data/BatF/bb left8.png") ||
			!BBTLeftFrame[9].loadFromFile("Data/BatF/bb left9.png")) {
			std::cerr << "Error loading left frame textures!" << std::endl;
		}

		// Load all right frame textures
		if (!BBTRightFrame[0].loadFromFile("Data/BatF/bb still.png") ||
			!BBTRightFrame[1].loadFromFile("Data/BatF/bb right1.png") ||
			!BBTRightFrame[2].loadFromFile("Data/BatF/bb right2.png") ||
			!BBTRightFrame[3].loadFromFile("Data/BatF/bb right3.png") ||
			!BBTRightFrame[4].loadFromFile("Data/BatF/bb right4.png") ||
			!BBTRightFrame[5].loadFromFile("Data/BatF/bb right5.png") ||
			!BBTRightFrame[6].loadFromFile("Data/BatF/bb right6.png") ||
			!BBTRightFrame[7].loadFromFile("Data/BatF/bb right7.png") ||
			!BBTRightFrame[8].loadFromFile("Data/BatF/bb right8.png") ||
			!BBTRightFrame[9].loadFromFile("Data/BatF/bb right9.png")) {
			std::cerr << "Error loading right frame textures!" << std::endl;
		}

		// Initialize all sprites
		for (int i = 0; i < 10; ++i) {
			BBSLeftFrame[i].setTexture(BBTLeftFrame[i]);
			BBSRightFrame[i].setTexture(BBTRightFrame[i]);
			BBSLeftFrame[i].setPosition(s_position_x, s_position_y);
			BBSRightFrame[i].setPosition(s_position_x, s_position_y);
			BBSLeftFrame[i].setScale(scaleFactor);
			BBSRightFrame[i].setScale(scaleFactor);
		}

		currentAnimationState = MOVING_RIGHT;
		animate();
	}
	void update(Player* player, int cellsize) override
	{
		if (movingright)
		{
			s_position_x += speed;
			if (s_position_x >= f_position_x)
			{
				movingright = false;
			}
			currentAnimationState = MOVING_RIGHT;
		}
		else
		{
			s_position_x -= speed;
			if (s_position_x <= f_position_x)
			{
				movingright = true;
			}
			currentAnimationState = MOVING_LEFT;
			animate();
		}
	}
	void render(sf::RenderWindow& window) override
	{
		if (movingright)
		{
			window.draw(BBSRightFrame[Lr]);

		}
		else
		{
			window.draw(BBSLeftFrame[Lf]);
		}
	}
	bool collision(Player* players) override {
		return false;
	}
	void life() override {}

	int getHp() const override { return hp; }
	int getHits() const override { return hits; }

	int getStartX() const override { return s_position_x; }
	int getStartY() const override { return s_position_y; }
	int getFinalX() const override { return f_position_x; }
	int getFinalY() const override { return f_position_y; }

	void setPosition(int x, int y) override {
		s_position_x = x;
		s_position_y = y;
		for (int i = 0; i < 3; ++i) {
			BBSLeftFrame[i].setPosition(x, y);
			BBSRightFrame[i].setPosition(x, y);
		}
	}
	void setScale(float scaleX, float scaleY) {
		scaleFactor.x = scaleX;
		scaleFactor.y = scaleY;
		for (int i = 0; i < 3; ++i) {
			BBSLeftFrame[i].setScale(scaleFactor);
			BBSRightFrame[i].setScale(scaleFactor);
		}
	}

	void flyBehavior() override {}
	void animate()
	{
		if (AnimationClock.getElapsedTime() >= timeperframe) {
			AnimationClock.restart();
			if (currentAnimationState == MOVING_LEFT) {
				Lf = (Lf + 1) % 3;
				std::cout << "Current left frame index: " << Lf << std::endl;
			}
			else if (currentAnimationState == MOVING_RIGHT) {
				Lr = (Lr + 1) % 3;
				std::cout << "Current right frame index: " << Lr << std::endl;
			}
		}

		switch (currentAnimationState) {
		case MOVING_LEFT:
		{
			
			BBSLeftFrame[Lf].setPosition(s_position_x, s_position_y);
			BBSLeftFrame[Lf].setScale(scaleFactor);
			break;
		}
		case MOVING_RIGHT:
		{
			BBSRightFrame[Lr].setPosition(s_position_x, s_position_y);
			BBSRightFrame[Lr].setScale(scaleFactor);
			break;
		}
		case UP:
			// Load idle left sprite (you might want to make this multi-frame as well)
			break;
		case DOWN:
			// Load idle right sprite (you might want to make this multi-frame as well)
			break;
		}
	}

};
class EggStinger :public Fly
{
	//loading textures for each
	sf::Texture textureLeftFrame[4];
	sf::Sprite spriteLeftFrame[4];
	sf::Texture textureRightFrame[4];
	sf::Sprite spriteRightFrame[4];
	sf::Texture textureUpFrame[3];
	sf::Sprite spriteUpFrame[3];
	sf::Texture textureDownFrame[3];
	sf::Sprite spriteDownFrame[3];
	int hp = 20;
	int hits = 0;
	//starting and final posotions
	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;
	//initial state
	bool movingRight = true;
	float speed = 3.0f;
	//not needed anymore
	sf::Vector2f scaleFactor = { 1.0f, 1.0f };
	//one clock for animation and one for action
	//animatin clock to change frame
	//action clock to destroy blocks after 5 sec or 5f
	sf::Clock animationClock;
	sf::Time frameTime = sf::seconds(0.15f);
	//for frames loading
	//like it restarts after frame index reches max value
	int currentLeftFrameIndex = 0; // Index to track the current left animation frame
	int currentRightFrameIndex = 0;
	int currentUpFrameIndex = 0;
	int currentDownFrameIndex = 0;
	sf::Clock actionClock;
	bool goingDown = false;
	bool goingUp = false;
	float originalY;
	//how much distance does the eggstinger comes down
	float dropDistance = 500.f;
	bool targetPlayer = false;

	bool hasRemovedBlock = false;

	char** grid;
public:
	EggStinger(int startX, int startY, int endX, int endY, char** lvl) :
		s_position_x(startX), s_position_y(startY), f_position_x(endX), f_position_y(endY), grid(lvl)
	{
		originalY = s_position_y;
		currentAnimationState = MOVING_RIGHT;



		if (!textureLeftFrame[0].loadFromFile("Data/eggstinger/Still.png") ||
			!textureLeftFrame[1].loadFromFile("Data/eggstinger/left3.png") ||
			!textureLeftFrame[2].loadFromFile("Data/eggstinger/left2.png") ||
			!textureLeftFrame[3].loadFromFile("Data/eggstinger/left1.png")) {
			std::cerr << "Error loading left frame textures!" << std::endl;
		}

		// Load right frames
		if (!textureRightFrame[0].loadFromFile("Data/eggstinger/Still.png") ||
			!textureRightFrame[1].loadFromFile("Data/eggstinger/right3.png") ||
			!textureRightFrame[2].loadFromFile("Data/eggstinger/right2.png") ||
			!textureRightFrame[3].loadFromFile("Data/eggstinger/right1.png")) {
			std::cerr << "Error loading right frame textures!" << std::endl;
		}

		// Load up frames
		if (!textureUpFrame[0].loadFromFile("Data/eggstinger/up.png") ||
			!textureUpFrame[1].loadFromFile("Data/eggstinger/up.png") ||
			!textureUpFrame[2].loadFromFile("Data/eggstinger/up.png")) {
			std::cerr << "Error loading up frame textures!" << std::endl;
		}

		// Load down frames
		if (!textureDownFrame[0].loadFromFile("Data/eggstinger/down1.png") ||
			!textureDownFrame[1].loadFromFile("Data/eggstinger/down2.png") ||
			!textureDownFrame[2].loadFromFile("Data/eggstinger/down3.png")) {
			std::cerr << "Error loading down frame textures!" << std::endl;
		}

		// Initialize sprites
		for (int i = 0; i < 4; i++) {
			spriteLeftFrame[i].setTexture(textureLeftFrame[i]);
			spriteRightFrame[i].setTexture(textureRightFrame[i]);
			spriteLeftFrame[i].setPosition(s_position_x, s_position_y);
			spriteRightFrame[i].setPosition(s_position_x, s_position_y);
			spriteLeftFrame[i].setScale(scaleFactor);
			spriteRightFrame[i].setScale(scaleFactor);
		}

		for (int i = 0; i < 3; i++) {
			spriteUpFrame[i].setTexture(textureUpFrame[i]);
			spriteDownFrame[i].setTexture(textureDownFrame[i]);
			spriteUpFrame[i].setPosition(s_position_x, s_position_y);
			spriteDownFrame[i].setPosition(s_position_x, s_position_y);
			spriteUpFrame[i].setScale(scaleFactor);
			spriteDownFrame[i].setScale(scaleFactor);
		}



		animate(); // Load initial sprite




		if (!hurtBuffer.loadFromFile("Data/Hurt.ogg"))
		{
			std::cerr << "Error loading jump sound!" << std::endl;
		}
		hurtSound.setBuffer(hurtBuffer);
		hurtSound.setVolume(30);


	}

	void update(Player* player, int cellSize) override {
		float playerX = player->getX();

		float playerY = player->getY();
		int x = 0;
		// Every 5 seconds, check if player is within X range to make the boss come down
		if (actionClock.getElapsedTime().asSeconds() > 5.0f && !goingDown && !goingUp) {
			if (std::abs(playerX - s_position_x) < 150) {  // to check the distance between player and eggstinger, if it is less than 150 than the egg stinger comes down
				int x = playerX;
				goingDown = true;
				targetPlayer = true;
				actionClock.restart();
			}
		}

		if (goingDown) {
			s_position_y += 10.0f; // go down
			if (!hasRemovedBlock) {

				// to find the location of 
				int gridX = x / cellSize;
				int gridx = s_position_x / cellSize;

				if (grid[11][gridx+1] == 'w') {
					grid[11][gridx+1] = ' ';
					hasRemovedBlock = true;

				}
			}

			if (s_position_y >= originalY + dropDistance) {

				goingDown = false;

				goingUp = true;
			}
			currentAnimationState = DOWN;
		}
		else if (goingUp) {
			s_position_y -= 10.0f;
			if (s_position_y <= originalY) {
				s_position_y = originalY;
				goingUp = false;
				targetPlayer = false;
			}
			currentAnimationState = UP;
			hasRemovedBlock = false;
		}
		else {
			// Regular patrol
			if (movingRight) {
				s_position_x += speed;
				if (s_position_x >= f_position_x)
					movingRight = false;
				currentAnimationState = MOVING_RIGHT;
			}
			else {
				s_position_x -= speed;
				if (s_position_x <= f_position_x - 1200)
					movingRight = true;
				currentAnimationState = MOVING_LEFT;
			}
		}

		animate();
	}
	void render(sf::RenderWindow& window) override {
		switch (currentAnimationState) {
		case MOVING_RIGHT:
			window.draw(spriteRightFrame[currentRightFrameIndex]);
			break;
		case MOVING_LEFT:
			window.draw(spriteLeftFrame[currentLeftFrameIndex]);
			break;
		case UP:
			window.draw(spriteUpFrame[currentUpFrameIndex]);
			break;
		case DOWN:
			window.draw(spriteDownFrame[currentDownFrameIndex]);
			break;
		}
	}

	


	bool collision(Player* players) override {
		sf::FloatRect crabBounds;
		if (movingRight) {
			crabBounds = spriteRightFrame[currentRightFrameIndex].getGlobalBounds();
		}
		else if(!movingRight){
			crabBounds = spriteLeftFrame[currentLeftFrameIndex].getGlobalBounds();
		}
		else if (goingDown)
		{
			crabBounds = spriteDownFrame[currentDownFrameIndex].getGlobalBounds();
		}
		else if (goingUp)
		{
			crabBounds = spriteUpFrame[currentUpFrameIndex].getGlobalBounds();
		}
		sf::FloatRect playerBounds = players->getSprite().getGlobalBounds();
		if (crabBounds.intersects(playerBounds)) {
			if (players->getIsJumping())
			{
				
				dead = true;
				return true;
			}
			else
			{
				cout << "OUCHHHH THAT HURTTTTTT" << endl;
				hurtSound.play();
				players->setHurtRight(movingRight);
				players->setHurt(true);

				return true;
			}

			cout << "OUCHHHH THAT HURTTTTTT" << endl;
		}
		return false;
	}


	void life() override {}

	int getHp() const override { return hp; }
	int getHits() const override { return hits; }

	int getStartX() const override { return s_position_x; }
	int getStartY() const override { return s_position_y; }
	int getFinalX() const override { return f_position_x; }
	int getFinalY() const override { return f_position_y; }

	void setPosition(int x, int y) override {
		s_position_x = x;
		s_position_y = y;
		for (int i = 0; i < 4; ++i) {
			spriteLeftFrame[i].setPosition(x, y);
			spriteRightFrame[i].setPosition(x, y);
		}
	}

	void flyBehavior() override {}

	void setScale(float scaleX, float scaleY) {
		scaleFactor.x = scaleX;
		scaleFactor.y = scaleY;
		for (int i = 0; i < 4; ++i) {
			spriteLeftFrame[i].setScale(scaleFactor);
			spriteRightFrame[i].setScale(scaleFactor);
		}
	}

	void animate() {
		if (animationClock.getElapsedTime() >= frameTime) {
			animationClock.restart();
			if (currentAnimationState == MOVING_LEFT) {
				currentLeftFrameIndex = (currentLeftFrameIndex + 1) % 4;
				std::cout << "Current left frame index: " << currentLeftFrameIndex << std::endl;
			}
			else if (currentAnimationState == MOVING_RIGHT) {
				currentRightFrameIndex = (currentRightFrameIndex + 1) % 4;
				std::cout << "Current right frame index: " << currentRightFrameIndex << std::endl;
			}
			else if (currentAnimationState == UP) {
				currentUpFrameIndex = (currentUpFrameIndex + 1) % 3;
				std::cout << "Current up frame index: " << currentUpFrameIndex << std::endl;
			}
			else if (currentAnimationState == DOWN) {
				currentDownFrameIndex = (currentDownFrameIndex + 1) % 3;
				std::cout << "Current down frame index: " << currentDownFrameIndex << std::endl;
			}


		}

		switch (currentAnimationState) {
		case MOVING_LEFT:
		{
			spriteLeftFrame[currentLeftFrameIndex].setPosition(s_position_x, s_position_y);
			spriteLeftFrame[currentLeftFrameIndex].setScale(scaleFactor);
			break;
		}
		case MOVING_RIGHT:
		{
			spriteRightFrame[currentRightFrameIndex].setPosition(s_position_x, s_position_y);
			spriteRightFrame[currentRightFrameIndex].setScale(scaleFactor);
			break;
		}
		case UP:
		{
			spriteUpFrame[currentUpFrameIndex].setPosition(s_position_x, s_position_y);
			spriteUpFrame[currentUpFrameIndex].setScale(scaleFactor);
			break;
		}
		case DOWN:
		{
			spriteDownFrame[currentDownFrameIndex].setPosition(s_position_x, s_position_y);
			spriteDownFrame[currentDownFrameIndex].setScale(scaleFactor);
			break;
		}
		}
	}
};
//

