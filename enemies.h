#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
class Enemies {
	protected:
		//int hp;
		//int hits;
		int s_position_x, s_position_y;
		int f_position_x, f_position_y;
		sf::Sprite sprite;
		sf::Texture texture;
		sf::Vector2f scaleFactor = { 1.0f, 1.0f };
	
protected://since so many enemies are sharing the same func
		//virtual void loadSprite(const std::string& path) = 0;
		static const int IDLE_LEFT = 0;
		static const int MOVING_LEFT = 1;
		static const int IDLE_RIGHT = 2;
		static const int MOVING_RIGHT = 3;

		int currentAnimationState;
public:
		virtual void update() = 0;
		virtual void render(sf::RenderWindow& window) = 0;
		virtual bool collision(int& playerHP) = 0;

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
		virtual void setScale(float scaleX, float scaleY);
		//enemies animations 
		virtual void playIdleLeftAnimation() {}
		virtual void playMovingLeftAnimation() {}
		virtual void playIdleRightAnimation() {}
		virtual void playMovingRightAnimation() {}
		virtual ~Enemies() {}
};
void Enemies::setScale(float scaleX, float scaleY) {
	scaleFactor.x = scaleX;
	scaleFactor.y = scaleY;
	sprite.setScale(scaleFactor);
}


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
		animate();
	}



	void update() override {
		if (movingRight) {
			s_position_x += speed;
			if (s_position_x >= f_position_x) movingRight = false;
			currentAnimationState = MOVING_RIGHT;
		}
		else {
			s_position_x -= speed;
			if (s_position_x <= f_position_x -1200) movingRight = true;
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

	bool collision(int& playerHP) override {
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
	void setScale(float scaleX, float scaleY) override {
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
				if (!textureLeft.loadFromFile("Data/Enemies/MBF/mottobug 1.png")) {
					std::cerr << "Error loading motto bug left frame 1 texture!" << std::endl;
				}
				cout << "frame 1 loaded" << endl;
				spriteLeft.setTexture(textureLeft);
				spriteLeft.setPosition(s_position_x, s_position_y);
				spriteLeft.setScale(scaleFactor);
			}
			else {
				if (!textureLeft1.loadFromFile("Data/Enemies/MBF/mottobug 7.png")) {
					std::cerr << "Error loading motto bug left frame 2 texture!" << std::endl;
				}
				cout << "frame 2 loaded" << endl;
				spriteLeft1.setTexture(textureLeft1);
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
				if (!textureRight.loadFromFile("Data/Enemies/MBF/mottobug 14(2).png")) {
					std::cerr << "Error loading motto bug right frame 1 texture!" << std::endl;
				}
				cout << "frame 3 loaded" << endl;
				spriteRight.setTexture(textureRight);
				spriteRight.setPosition(s_position_x, s_position_y);
				spriteRight.setScale(scaleFactor);
			}
			else
			{
				if (!textureRight1.loadFromFile("Data/Enemies/MBF/mottobug 7(2).png"))
				{
					std::cerr << "Error loading motto bug right frame 2 texture!" << std::endl;
				}
				cout << "frame 4 loaded" << endl;
				spriteRight1.setTexture(textureRight1);
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
		animate(); // Load initial sprite

	}

	void update() override {
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

	bool collision(int& playerHP) override {
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

	void setScale(float scaleX, float scaleY) override {
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
			std::string texturePath;
			switch (currentLeftFrameIndex) {
			case 0: texturePath = "Data/CMF/crab meat 2.png"; break;
			case 1: texturePath = "Data/CMF/crab meat 10.png"; break;
			case 2: texturePath = "Data/CMF/crab meat 5.png"; break;
			}
			if (!textureLeftFrame[currentLeftFrameIndex].loadFromFile(texturePath)) {
				std::cerr << "Error loading left frame " << currentLeftFrameIndex + 1 << " texture!" << std::endl;
			}
			spriteLeftFrame[currentLeftFrameIndex].setTexture(textureLeftFrame[currentLeftFrameIndex]);
			spriteLeftFrame[currentLeftFrameIndex].setPosition(s_position_x, s_position_y);
			spriteLeftFrame[currentLeftFrameIndex].setScale(scaleFactor);
			break;
		}
		case MOVING_RIGHT:
		{
			std::string texturePath;
			switch (currentRightFrameIndex) {
			case 0: texturePath = "Data/CMF/crab meat 7.png"; break;
			case 1: texturePath = "Data/CMF/crab meat 9.png"; break;
			case 2: texturePath = "Data/CMF/crab meat 6.png"; break;
			}
			if (!textureRightFrame[currentRightFrameIndex].loadFromFile(texturePath)) {
				std::cerr << "Error loading right frame " << currentRightFrameIndex + 1 << " texture!" << std::endl;
			}
			spriteRightFrame[currentRightFrameIndex].setTexture(textureRightFrame[currentRightFrameIndex]);
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
//class BatBrain :public Fly
//{
//	bool goingUp = true;
//	float speed = 0.8f;
//	float verticalRange = 64 * 3;  // moves up/down 3 cells (each 64 px)
//	sf::Texture texture;
//	sf::Sprite sprite;
//	int hp = 2;
//	int hits = 0;
//
//	int s_position_x;
//	int s_position_y;
//	int f_position_x;
//	int f_position_y;
//
//	bool movingRight = true;
//	float speed = 8.0f;
//
//public:
//	BatBrain(int startX, int startY, int endX, int endY) {
//		s_position_x = startX;
//		s_position_y = startY;
//		f_position_x = endX;
//		f_position_y = endY;
//		hp = 2;
//		hits = 0;
//	}
//
//	void loadSprite(const std::string& path) override {
//		texture.loadFromFile(path);
//		sprite.setTexture(texture);
//		sprite.setPosition(s_position_x, s_position_y);
//	}
//
//	void update() override {
//		if (goingUp) {
//			s_position_y -= speed;
//			if (s_position_y <= f_position_y - verticalRange)
//				goingUp = false;
//		}
//		else {
//			s_position_y += speed;
//			if (s_position_y >= f_position_y)
//				goingUp = true;
//		}
//		sprite.setPosition(s_position_x, s_position_y);
//	}
//
//	void render(sf::RenderWindow& window) override {
//		window.draw(sprite);
//	}
//
//	bool collision(int& playerHP) override {
//		// Add AABB collision detection if needed
//		return false;
//	}
//
//	void life() override {
//		if (hp <= 0)
//			std::cout << "BeeBot defeated!" << std::endl;
//	}
//
//	int getHp() const override { return hp; }
//	int getHits() const override { return hits; }
//
//	int getStartX() const override { return s_position_x; }
//	int getStartY() const override { return s_position_y; }
//	int getFinalX() const override { return f_position_x; }
//	int getFinalY() const override { return f_position_y; }
//
//	void setPosition(int x, int y) override {
//		s_position_x = x;
//		s_position_y = y;
//		sprite.setPosition(x, y);
//	}
//
//	void flyBehavior() override {
//		// Special attack or movement logic (e.g., firing projectiles)
//	}
//	void setScale(float scaleX, float scaleY) override {
//		scaleFactor.x = scaleX;
//		scaleFactor.y = scaleY;
//		sprite.setScale(scaleFactor);
//	}
//};
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
		animate(); // Load initial sprite

	}

	void update() override {
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

	bool collision(int& playerHP) override {
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

	void setScale(float scaleX, float scaleY) override {
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
			std::string texturePath;
			switch (currentLeftFrameIndex) {
			case 0: texturePath = "Data/BBF/bee 1.png"; break;
			case 1: texturePath = "Data/BBF/bee2.png"; break;
			case 2: texturePath = "Data/BBF/bee3.png"; break;
			}
			if (!textureLeftFrame[currentLeftFrameIndex].loadFromFile(texturePath)) {
				std::cerr << "Error loading left frame " << currentLeftFrameIndex + 1 << " texture!" << std::endl;
			}
			spriteLeftFrame[currentLeftFrameIndex].setTexture(textureLeftFrame[currentLeftFrameIndex]);
			spriteLeftFrame[currentLeftFrameIndex].setPosition(s_position_x, s_position_y);
			spriteLeftFrame[currentLeftFrameIndex].setScale(scaleFactor);
			break;
		}
		case MOVING_RIGHT:
		{
			std::string texturePath;
			switch (currentRightFrameIndex) {
			case 0: texturePath = "Data/BBF/bee 1(rt).png"; break;
			case 1: texturePath = "Data/BBF/bee2(rt).png"; break;
			case 2: texturePath = "Data/BBF/bee3(rt).png"; break;
			}
			if (!textureRightFrame[currentRightFrameIndex].loadFromFile(texturePath)) {
				std::cerr << "Error loading right frame " << currentRightFrameIndex + 1 << " texture!" << std::endl;
			}
			spriteRightFrame[currentRightFrameIndex].setTexture(textureRightFrame[currentRightFrameIndex]);
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
//class EggStinger :public Fly
//{
//	bool goingUp = true;
//	float speed = 0.8f;
//	float verticalRange = 64 * 3;  // moves up/down 3 cells (each 64 px)
//
//
//public:
//	EggStinger(int startX, int startY, int endX, int endY) {
//		s_position_x = startX;
//		s_position_y = startY;
//		f_position_x = endX;
//		f_position_y = endY;
//		hp = 2;
//		hits = 0;
//	}
//
//	void loadSprite(const std::string& path) override {
//		texture.loadFromFile(path);
//		sprite.setTexture(texture);
//		sprite.setPosition(s_position_x, s_position_y);
//	}
//
//	void update() override {
//		if (goingUp) {
//			s_position_y -= speed;
//			if (s_position_y <= f_position_y - verticalRange)
//				goingUp = false;
//		}
//		else {
//			s_position_y += speed;
//			if (s_position_y >= f_position_y)
//				goingUp = true;
//		}
//		sprite.setPosition(s_position_x, s_position_y);
//	}
//
//	void render(sf::RenderWindow& window) override {
//		window.draw(sprite);
//	}
//
//	bool collision(int& playerHP) override {
//		
//		return false;
//	}
//
//	void life() override {
//		if (hp <= 0)
//			std::cout << "BeeBot defeated!" << std::endl;
//	}
//
//	int getHp() const override { return hp; }
//	int getHits() const override { return hits; }
//
//	int getStartX() const override { return s_position_x; }
//	int getStartY() const override { return s_position_y; }
//	int getFinalX() const override { return f_position_x; }
//	int getFinalY() const override { return f_position_y; }
//
//	void setPosition(int x, int y) override {
//		s_position_x = x;
//		s_position_y = y;
//		sprite.setPosition(x, y);
//	}
//
//	void flyBehavior() override {		
//	}
//	void setScale(float scaleX, float scaleY) override {
//		scaleFactor.x = scaleX;
//		scaleFactor.y = scaleY;
//		sprite.setScale(scaleFactor);
//	}
//};
//

