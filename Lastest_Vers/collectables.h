#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"character.h"
using namespace std;

class Collectibles {
protected:
    int s_position_x, s_position_y;
    sf::Vector2f scaleFactor = { 1.0f, 1.0f };
    bool on = true;

public:
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool collision(Player* player) = 0;

    virtual void initializeGrid(char** lvl, int height, int width, int level) = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual void setScaleC(float scaleX, float scaleY) = 0;
    virtual void loadSprites() = 0;
    bool getOn() { return on; }
    virtual ~Collectibles() {}
};
class Rings : public Collectibles {
private:
    sf::Texture RingTex[4];
    sf::Sprite RingSp[4];
    sf::Clock animationClock;
    sf::Time frameTime = sf::seconds(0.15f);
    int currentFrameIndex = 0;
    sf::SoundBuffer ringBuffer;
    sf::Sound ringSound;
public:
    Rings(int x = 0, int y = 0) {
        setPosition(x, y);
    }

    void loadSprites() override
    {
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
        if (!ringBuffer.loadFromFile("Data/Ring.ogg")) {
            std::cerr << "Error loading ring sound!" << std::endl;
        }
        ringSound.setBuffer(ringBuffer);
        ringSound.setVolume(30);
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

    bool collision(Player* player) override {
        if (abs(player->getX() - s_position_x) < 45 && abs(player->getY() - s_position_y) < 45)
        {
            cout << "YAYYYYYYYYYYYY!!! COllison detected!!";
            int r = player->getRingsCollected();
            player->setRingsCollected(++r);
            ringSound.play();
            on = false;
            player->setScore(player->getScore() + 20);
            return true;
        }
        else
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

    void initializeGrid(char** lvl, int height, int width, int level) override
    {
        switch (level) {
        case 1:

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (5 + i < height && 25 + j < width)
                        lvl[5 + i][25 + j] = 'r';
                    if (5 + i < height && 15 + j < width)
                        lvl[5 + i][16 + j] = 'r';
                    if (5 + i < height && 20 + j < width)
                        lvl[5 + i][20 + j] = 'r';
                    /*if (3 + i < height && 47 + j < width)
                        lvl[4 + i][47 + j] = 'r';*/
                }
                for (int i = 0; i < width; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        lvl[3][37 + j] = 'r';
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
                        lvl[height - 7][142 + j] = 'r';
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
                            lvl[height - 7][159 + i] = 'r';
                            lvl[height - 6][159 + i] = 'r';
                            lvl[height - 5][159 + i] = 'r';
                            lvl[height - 4][159 + i] = 'r';
                        }

                        for (int i = 0; i < 2; i++)
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
            break;
        case 2:
            for (int i = 0; i < 9; i++)
            {
                lvl[height - 9][i + 11] = 'r';
                lvl[height - 10][i + 11] = 'r';

                lvl[height - 11][i + 21] = 'r';
                lvl[height - 10][i + 21] = 'r';
            }
            for (int i = 0; i < 2; i++)
            {
                lvl[height - 5][i + 40] = 'r';
                lvl[height - 6][i + 42] = 'r';
                lvl[height - 7][i + 44] = 'r';
                lvl[height - 8][i + 46] = 'r';
                lvl[height - 9][i + 70] = 'r';
            }
            for (int i = 0; i < 4; i++)
            {
                if (i < 9)
                {
                    lvl[3][68 + i] = 'r';
                    lvl[4][68 + i] = 'r';
                    lvl[5][68 + i] = 'r';
                }

            }
            for (int i = 0; i < 11; i++)
            {
                lvl[i][90] = 'r';
                lvl[i][91] = 'r';
            }
            for (int i = 0; i < 4; i++)
            {
                lvl[5][114 + i] = 'r';
                lvl[6][114 + i] = 'r';
                lvl[7][114 + i] = 'r';
                lvl[8][114 + i] = 'r';
            }
            for (int i = 0; i < 5; i++)
            {
                lvl[height - 8][i + 141] = 'r';
                lvl[height - 8][i + 151] = 'r';
                lvl[height - 9][i + 141] = 'r';
                lvl[height - 9][i + 151] = 'r';
            }
            lvl[height - 6][176] = 'r';
            lvl[height - 6][181] = 'r';
            lvl[height - 6][186] = 'r';
            lvl[height - 6][191] = 'r';
            lvl[height - 6][196] = 'r';
            lvl[height - 6][201] = 'r';
            lvl[height - 6][206] = 'r';

            lvl[height - 9][174] = 'r';
            lvl[height - 9][178] = 'r';
            lvl[height - 9][184] = 'r';
            lvl[height - 9][188] = 'r';
            lvl[height - 9][194] = 'r';
            lvl[height - 9][198] = 'r';
            lvl[height - 9][204] = 'r';

            lvl[height - 12][176] = 'r';
            lvl[height - 12][181] = 'r';
            lvl[height - 12][186] = 'r';
            lvl[height - 12][191] = 'r';
            lvl[height - 12][196] = 'r';
            lvl[height - 12][201] = 'r';
            lvl[height - 12][206] = 'r';


            break;
        }

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

    void setPosition(int x, int y) override {
        s_position_x = x;
        s_position_y = y;
        for (int i = 0; i < 9; ++i) {
            BoastSp[i].setPosition(x, y);
        }
    }

    bool collision(Player* player) override {
        if (abs(player->getX() - s_position_x) < 45 && abs(player->getY() - s_position_y) < 45)
        {
            cout << "YAYYYYYYYYYYYY!!! COllison detected!!";
            player->setPowerUp(true);
            on = false;
            return true;
        }
        else
            return false;
    }

    void setScaleC(float scaleX, float scaleY) override {
        scaleFactor.x = 4.0f;
        scaleFactor.y = 4.0f;
        for (int i = 0; i < 9; ++i) {
            BoastSp[i].setScale(scaleFactor);
        }
    }

    void initializeGrid(char** lvl, int height, int width, int level) override
    {
        switch (level)
        {
        case 1:
            for (int i = 0; i < width; i++)
            {
                lvl[2][63] = 'u';
            }
            break;
        case 2:
            for (int i = 0; i < width; i++)
            {
                lvl[height - 5][55] = 'u';

            }
            break;
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

    bool collision(Player* player) override {
        if (abs(player->getX() - s_position_x) < 45 && abs(player->getY() - s_position_y) < 45)
        {
            cout << "YAYYYYYYYYYYYY!!! COllison detected!!";
            int r = player->getHp();
            player->setHp(++r);
            on = false;
            return true;
        }
        else
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

    void initializeGrid(char** lvl, int height, int width, int level) override {
        switch (level)
        {
        case 1:

            lvl[height - 5][130] = 'h';

            break;
        case 2:

            lvl[height - 5][172] = 'h';
            lvl[height - 5][210] = 'h';

            break;
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