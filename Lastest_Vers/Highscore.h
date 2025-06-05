L#pragma once
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
#include<../SuperSonic/menu.h>
#include"Level.h"
using namespace sf;
using namespace std;
class Highscore
{
    Font font;
    const int MAX_SCORES = 3;
    const int MENU_SIZE = 3;
    std::string name;
    std::string highScoreNames[3]; int highScores[3];

    Sprite background;
    Texture backgroundt;
public:
    Highscore(Font f)
    {
        font = f;
        backgroundt.loadFromFile("Data/mainmenu.png");
    }
    void savePlayerData(int score) {
        // Step 1: Read existing data from file
        std::vector<std::pair<std::string, int>> playerData;
        std::ifstream file("player_data.txt");

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                size_t commaPos = line.find(',');
                if (commaPos != std::string::npos) {
                    std::string playerName = line.substr(0, commaPos);
                    int playerScore = std::stoi(line.substr(commaPos + 1));
                    playerData.push_back({ playerName, playerScore });
                }
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open file to load data!" << std::endl;
        }

        // Step 2: Add the new player's data
        playerData.push_back({ name, score });

        // Step 3: Sort the data by score in descending order
        std::sort(playerData.begin(), playerData.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
            });

        // Step 4: Write the sorted data back to the file
        std::ofstream outFile("player_data.txt", std::ios::trunc);

        if (outFile.is_open()) {
            for (const auto& player : playerData) {
                outFile << player.first << "," << player.second << "\n";
            }
            outFile.close();
        }
        else {
            std::cerr << "Unable to open file to save data!" << std::endl;
        }
    }
    void getPlayerName(sf::RenderWindow& window) {
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2u imageSize = backgroundt.getSize();
        float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
        float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
        background.setTexture(backgroundt);
        background.setScale(scaleX, scaleY);
        sf::Text prompt("Enter your name: ", font, 100);
        prompt.setPosition(100, 200);
        sf::Text inputText("", font, 100);
        inputText.setPosition(100, 250);

        sf::String input;
        bool nameEntered = false;

        while (window.isOpen() && !nameEntered) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }

                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 8 && input.getSize() > 0) { // Backspace
                        input.erase(input.getSize() - 1, 1);
                    }
                    else if (event.text.unicode == 13) { // Enter key
                        name = input.toAnsiString();
                        nameEntered = true;
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != 13) {
                        input += event.text.unicode;
                    }
                }
            }

            inputText.setString(input);

            window.clear();
            window.draw(background);
            window.draw(prompt);
            window.draw(inputText);
            window.display();
        }
    }
    void getHighScores() {
        std::ifstream file("player_data.txt");
        if (file.is_open()) {
            std::string line;
            int count = 0;

            for (int i = 0; i < MAX_SCORES; ++i) {
                highScores[i] = 0;
                highScoreNames[i] = "";
            }
            while (std::getline(file, line) && count < 3) {
                size_t commaPos = line.find(',');
                if (commaPos != std::string::npos) {
                    std::string name = line.substr(0, commaPos);
                    int score = std::stoi(line.substr(commaPos + 1));
                    highScoreNames[count] = name;
                    highScores[count] = score;
                    ++count;
                }
            }

            file.close();
        }
        else {
            std::cerr << "Unable to open file to read high scores!" << std::endl;
        }
    }
    void displayHighScores(sf::RenderWindow& window) {
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2u imageSize = backgroundt.getSize();
        float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
        float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
        background.setTexture(backgroundt);
        background.setScale(scaleX, scaleY);
        sf::Text title("High Scores", font, 100);
        title.setFillColor(sf::Color::Yellow);
        title.setPosition(300, 50);

        sf::Text scores[3];
        for (int i = 0; i < MAX_SCORES; ++i) {
            scores[i].setFont(font);
            scores[i].setString(std::to_string(i + 1) + ". " + highScoreNames[i] + " - " + std::to_string(highScores[i]));
            scores[i].setCharacterSize(80);
            scores[i].setFillColor(sf::Color::Black);
            scores[i].setPosition(300, 350 + i * 50);
        }

       // sf::Text backButton("Press B to go back", font, 24);
        //backButton.setFillColor(sf::Color::Green);
        //backButton.setPosition(300, 400);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
                    return;
                }
            }

            window.clear();
            window.draw(background);
            window.draw(title);
            for (int i = 0; i < MAX_SCORES; ++i) {
                window.draw(scores[i]);
            }
           // window.draw(backButton);
            window.display();
        }
    }
};