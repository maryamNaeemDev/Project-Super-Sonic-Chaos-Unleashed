#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
class Rings;

class Collectibles {
protected:
	int s_position_x, s_position_y;
	sf::Vector2f scaleFactor = { 1.0f, 1.0f };

public:
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual bool collision(int& playerX, int& playerY) = 0;

   virtual void initializeGrid(char** lvl, int height, int width)=0;
   virtual void setPosition(int x, int y) = 0;
	virtual void setScaleC(float scaleX, float scaleY) = 0;
	virtual void loadSprites() = 0;

	virtual ~Collectibles() {}
};
class Rings : public Collectibles {
private:
    sf::Texture RingTex[4];
    sf::Sprite RingSp[4];
    sf::Clock animationClock;
    sf::Time frameTime = sf::seconds(0.15f);
    int currentFrameIndex = 0;

public:
    Rings(int x = 0, int y = 0) {
        setPosition(x, y);
    }

    void loadSprites() override {
        std::string paths[4] = {
            "Data/collectibles/ringfull/rings1.png",
            "Data/collectibles/ringfull/rings2.png",
            "Data/collectibles/ringfull/rings3.png",
            "Data/collectibles/ringfull/rings4.png"
        };

        for (int i = 0; i < 4; ++i) {
            if (!RingTex[i].loadFromFile(paths[i])) {
                std::cerr << "Error loading texture " << paths[i] << "\n";
            }
            RingSp[i].setTexture(RingTex[i]);
            RingSp[i].setScale(scaleFactor);
            RingSp[i].setPosition(s_position_x, s_position_y);
        }
    }

    void render(sf::RenderWindow& window) override {
        window.draw(RingSp[currentFrameIndex]);
    }

    void update() override {
        if (animationClock.getElapsedTime() >= frameTime) {
            animationClock.restart();
            currentFrameIndex = (currentFrameIndex + 1) % 4;
        }
    }

    bool collision(int& playerX, int& playerY) override {
        return false;
    }

    void setPosition(int x, int y) override {
        s_position_x = x;
        s_position_y = y;
        for (int i = 0; i < 4; ++i) {
            RingSp[i].setPosition(x, y);
        }
    }

    void setScaleC(float scaleX, float scaleY) override {
        scaleFactor.x = scaleX;
        scaleFactor.y = scaleY;
        for (int i = 0; i < 4; ++i) {
            RingSp[i].setScale(scaleFactor);
        }
    }
   
    void initializeGrid(char** lvl, int height, int width) override {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (5 + i < height && 25 + j < width)
                    lvl[5 + i][25+ j] = 'r';
                if (5 + i < height && 15 + j < width)
                    lvl[5 + i][16 + j] = 'r';
                if (5 + i < height && 20 + j < width)
                    lvl[5 + i][20 + j] = 'r';
				/*if (3 + i < height && 47 + j < width)
					lvl[4 + i][47 + j] = 'r';*/
            }
            for (int i = 0;i < width;i++)
            {
                for (int j = 0;j <5;j++)
                {
					lvl[3][37+j] = 'r';
                    lvl[4][37 + j] = 'r';
                    lvl[5][37 + j] = 'r';
                    if (j < 2)
                    {
                        lvl[6][37 + j] = 'r';
						lvl[6][40 + j] = 'r';
						

                    }
                    if (i < 3)
                    {
                        lvl[5 + i][52] = 'r';
                        lvl[3 + i][56] = 'r';
                    }
					if (i < 2)
					{
						lvl[4 + i][68] = 'r';
                        lvl[4 + i][69] = 'r';
                        lvl[4 + i][73] = 'r';
                        lvl[4 + i][74] = 'r';
                        lvl[4 + i][81] = 'r';
                        lvl[4 + i][82] = 'r';
                        lvl[4 + i][86] = 'r';
                        lvl[4 + i][87] = 'r';
					}
                    lvl[height - 4][106] = 'r';
                    lvl[height - 5][107] = 'r';
                    lvl[height - 6][108] = 'r';
                    lvl[height - 7][109] = 'r';
                    lvl[height - 8][110] = 'r';
                    lvl[height - 9][111] = 'r';
                    lvl[height - 10][112] = 'r';
                    lvl[height - 11][113] = 'r';

                    lvl[height - 8][142 + j] = 'r';
                    lvl[height-7][142 + j] = 'r';
                    lvl[height - 6][142 + j] = 'r';
                    lvl[height - 5][142 + j] = 'r';
                    if (j < 2)
                    {
                        lvl[height - 4][142 + j] = 'r';
                        lvl[height - 4][145 + j] = 'r';

                    }
                    for (int i = 0; i < 8; i++)
                    {
                        lvl[height - 8][159 + i] = 'r';
                        lvl[height-7][159 + i] = 'r';
                        lvl[height-6][159 + i] = 'r';
                        lvl[height-5][159 + i] = 'r';
                        lvl[height-4][159 + i] = 'r';
                    }

                    for (int i=0 ;i< 2;i++)
                    {
                        lvl[4][178 + i] = 'r';
                        lvl[5][178 + i] = 'r';
                        lvl[4][181 + i] = 'r';
                        lvl[5][181 + i] = 'r';
                        lvl[4][184 + i] = 'r';
                        lvl[5][184 + i] = 'r';
                        lvl[4][187 + i] = 'r';
                        lvl[5][187 + i] = 'r';
                    }
                }

            }
        }
        /*for (int i = 0;i<width;i++)
        {
            lvl[5][36] = 'r';
        }*/
    }
    void placeOnGrid(char** lvl, int height, int width, Rings**& ringArray, int& count) 
    {
        count = 0;

        // First count how many rings
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                if (lvl[i][j] == 'r')
                    count++;

        ringArray = new Rings * [count];
        int index = 0;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (lvl[i][j] == 'r') {
                    ringArray[index] = new Rings(j * 64, i * 64);  // 50 = tile size
                    ringArray[index]->setScaleC(scaleFactor.x, scaleFactor.y);
                    ringArray[index]->loadSprites();
                    ++index;
                }
            }
        }
    }

   
};

class Boast : public Collectibles
{
private:
    sf::Texture BoastTex[9];
    sf::Sprite BoastSp[9];
    sf::Clock animationClock;
    sf::Time frameTime = sf::seconds(0.05f);
    int currentFrameIndex = 0;

public:
    Boast(int x = 0, int y = 0) {
        setPosition(x, y);
    }

    void loadSprites() override {
        std::string paths[9] = {
            "Data/collectibles/pufull/pu1.png",
            "Data/collectibles/pufull/pu2.png",
            "Data/collectibles/pufull/pu3.png",
           "Data/collectibles/pufull/pu4.png",
            "Data/collectibles/pufull/pu5.png",
            "Data/collectibles/pufull/pu6.png",
            "Data/collectibles/pufull/pu7.png",
            "Data/collectibles/pufull/pu8.png",
            "Data/collectibles/pufull/pu9.png",
        };

        for (int i = 0; i < 9; ++i) {
            if (!BoastTex[i].loadFromFile(paths[i])) {
                std::cerr << "Error loading texture " << paths[i] << "\n";
            }
            BoastSp[i].setTexture(BoastTex[i]);
            BoastSp[i].setScale(scaleFactor);
            BoastSp[i].setPosition(s_position_x, s_position_y);
        }
    }

    void render(sf::RenderWindow& window) override {
        window.draw(BoastSp[currentFrameIndex]);
    }

    void update() override {
        if (animationClock.getElapsedTime() >= frameTime) {
            animationClock.restart();
            currentFrameIndex = (currentFrameIndex + 1) % 9;
        }
    }

    bool collision(int& playerX, int& playerY) override {
        return false;
    }

    void setPosition(int x, int y) override {
        s_position_x = x;
        s_position_y = y;
        for (int i = 0; i < 9; ++i) {
            BoastSp[i].setPosition(x, y);
        }
    }

    void setScaleC(float scaleX, float scaleY) override {
        scaleFactor.x = 4.0f;
        scaleFactor.y = 4.0f;
        for (int i = 0; i < 9; ++i) {
            BoastSp[i].setScale(scaleFactor);
        }
    }

    void initializeGrid(char** lvl, int height, int width) override 
    {
       
            for (int i = 0;i < width;i++)
            {
				lvl[2][63] = 'u';
            }
    }
       
    void placeOnGrid(char** lvl, int height, int width, Boast**& boastArray, int& count)
    {
        count = 0;

        // First count how many rings
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                if (lvl[i][j] == 'u')
                    count++;

        boastArray = new Boast * [count];
        int index = 0;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (lvl[i][j] == 'u') {
                    boastArray[index] = new Boast(j * 64, i * 64);  // 50 = tile size
                    boastArray[index]->setScaleC(scaleFactor.x, scaleFactor.y);
                    boastArray[index]->loadSprites();
                    ++index;
                }
            }
        }
    }


};
class Life : public Collectibles
{
private:
sf::Texture PowerTex[4];
sf::Sprite PowerSp[4];
sf::Clock animationClock;
sf::Time frameTime = sf::seconds(0.15f);
int currentFrameIndex = 0;

public:
    Life(int x = 0, int y = 0) {
        setPosition(x, y);
    }

    void loadSprites() override {
        std::string paths[4] = 
        {
           "Data/collectibles/life full/life1.png",
            "Data/collectibles/life full/life2.png",
            "Data/collectibles/life full/life3.png",
            "Data/collectibles/life full/life4.png"
        };

        for (int i = 0; i < 4; ++i) {
            if (!PowerTex[i].loadFromFile(paths[i]))
            {
                std::cerr << "Error loading texture " << paths[i] << "\n";
            }
            PowerSp[i].setTexture(PowerTex[i]);
            PowerSp[i].setScale(scaleFactor);
            PowerSp[i].setPosition(s_position_x, s_position_y);
        }
    }

    void render(sf::RenderWindow& window) override {
        window.draw(PowerSp[currentFrameIndex]);
    }

    void update() override {
        if (animationClock.getElapsedTime() >= frameTime) {
            animationClock.restart();
            currentFrameIndex = (currentFrameIndex + 1) % 4;
        }
    }

    bool collision(int& playerX, int& playerY) override {
        return false;
    }

    void setPosition(int x, int y) override {
        s_position_x = x;
        s_position_y = y;
        for (int i = 0; i < 4; ++i) {
            PowerSp[i].setPosition(x, y);
        }
    }

    void setScaleC(float scaleX, float scaleY) override {
        scaleFactor.x = 5.0;
        scaleFactor.y = 5.0;
        for (int i = 0; i < 4; ++i) {
            PowerSp[i].setScale(scaleFactor);
        }
    }

    void initializeGrid(char** lvl, int height, int width) override {
        for (int i = 0;i < height;i++)
        {
            lvl[height-5][130] = 'h';
        }
    }
    void placeOnGrid(char** lvl, int height, int width, Life**& lifeArray, int& count)
    {
        count = 0;

        // First count how many rings
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                if (lvl[i][j] == 'h')
                    count++;

        lifeArray = new Life * [count];
        int index = 0;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (lvl[i][j] == 'h')
                {
                    lifeArray[index] = new Life(j * 64, i * 64);  // 50 = tile size
                    lifeArray[index]->setScaleC(scaleFactor.x, scaleFactor.y);
                    lifeArray[index]->loadSprites();
                    ++index;
                }
            }
        }
    }

};