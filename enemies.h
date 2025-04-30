#pragma once

class Enemies {
	protected:
		int hp;
		int hits;
		int s_position_x, s_position_y;
		int f_position_x, f_position_y;
		sf::Sprite sprite;
		sf::Texture texture;
		sf::Vector2f scaleFactor = { 1.0f, 1.0f };
	
protected://since so many enemies are sharing the same func
		virtual void loadSprite(const std::string& path) = 0;
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

class MottoBug : public Crawl {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int hp = 2;
	int hits = 0;

	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;

	bool movingRight = true;
	float speed = 8.0f;

public:
	MottoBug(int startX, int startY, int endX, int endY) {
		s_position_x = startX;
		s_position_y = startY;
		f_position_x = endX;
		f_position_y = endY;
	}

	void loadSprite(const std::string& path) override {
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		sprite.setPosition(s_position_x, s_position_y);
	}

	void update() override {
		if (movingRight) {
			s_position_x += speed;
			if (s_position_x >= f_position_x) movingRight = false;
		}
		else {
			s_position_x -= speed;
			if (s_position_x <= f_position_x-1200 ) movingRight = true;
		}
		sprite.setPosition(s_position_x, s_position_y);
	}

	void render(sf::RenderWindow& window) override {
		window.draw(sprite);
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
		
		sprite.setPosition(x, y);
	}
	
	void crawlBehavior() override {
		// Can be left empty unless needed
	}
	void setScale(float scaleX, float scaleY) override {
		scaleFactor.x = scaleX;
		scaleFactor.y = scaleY;
		sprite.setScale(scaleFactor);
	}
};



class CrabMeat :public Crawl
{
	
	sf::Texture texture;
	sf::Sprite sprite;
	int hp = 2;
	int hits = 0;

	int s_position_x;
	int s_position_y;
	int f_position_x;
	int f_position_y;

	bool movingRight = true;
	float speed = 8.0f;
	public:
		CrabMeat(int startX, int startY, int endX, int endY) {
			s_position_x = startX;
			s_position_y = startY;
			f_position_x = endX;
			f_position_y = endY;
			hp = 2;
			hits = 0;
		}

		void loadSprite(const std::string& path) override {
			texture.loadFromFile(path);
			sprite.setTexture(texture);
			sprite.setPosition(s_position_x, s_position_y);
		}

		void update() override {
			if (movingRight) {
				s_position_x += speed;
				if (s_position_x >= f_position_x) movingRight = false;
			}
			else {
				s_position_x -= speed;
				if (s_position_x <= f_position_x - 100) movingRight = true;
			}
			sprite.setPosition(s_position_x, s_position_y);
		}

		void render(sf::RenderWindow& window) override {
			window.draw(sprite);
		}

		bool collision(int& playerHP) override {
			
			return false;
		}

		void life() override {
			if (hp <= 0)
				std::cout << "MottoBug defeated!" << std::endl;
		}

		int getHp() const override { return hp; }
		int getHits() const override { return hits; }

		int getStartX() const override { return s_position_x; }
		int getStartY() const override { return s_position_y; }
		int getFinalX() const override { return f_position_x; }
		int getFinalY() const override { return f_position_y; }

		void setPosition(int x, int y) override {
			s_position_x = x;
			s_position_y = y;
			sprite.setPosition(x, y);
		}

		void crawlBehavior() override {
			
		}
		void setScale(float scaleX, float scaleY) override {
			scaleFactor.x = scaleX;
			scaleFactor.y = scaleY;
			sprite.setScale(scaleFactor);
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
//class BeeBot :public Fly
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
//	BeeBot(int startX, int startY, int endX, int endY) {
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
//			cout << "BeeBot defeated!" << endl;
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
//		
//	}
//	void setScale(float scaleX, float scaleY) override {
//		scaleFactor.x = scaleX;
//		scaleFactor.y = scaleY;
//		sprite.setScale(scaleFactor);
//	}
//};
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

