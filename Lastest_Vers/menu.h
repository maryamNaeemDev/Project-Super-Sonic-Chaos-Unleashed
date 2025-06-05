#pragma once
#include<iostream>
#include<string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;
class Menu
{
	string menuoptions[5] = { "Start Game", "Levels","Continue", "High Scores", "Settings" };
	Font font;
	Color normalColor = Color::Black;
	Color selectedColor = Color::Yellow;
	float menuItemSize = 70.f;
	float padding = 50.f;
	int selectedOption = 0;
	bool menuActive = true;
	int actionTaken = -1;
	string levelOptions[4] = { "Level 1", "Level 2", "Level 3", "Level 4" };
	int selectedLevel = 0;
	bool levelMenuActive = false;
	Sprite background;
	Texture backgroundt;
public:
	Menu(Font fontas)
	{
		font = fontas;
		backgroundt.loadFromFile("Data/mainmenu.png");
	}
	void displayMenu(RenderWindow& window)
	{
		sf::Vector2u windowSize = window.getSize();
		sf::Vector2u imageSize = backgroundt.getSize();
		float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
		float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
		background.setTexture(backgroundt);
		background.setScale(scaleX, scaleY);
		window.clear(Color::Black);
		Text title("Super Sonic", font, 100);
		title.setFillColor(Color::Cyan);
		title.setStyle(Text::Bold);
		FloatRect titleBounds = title.getLocalBounds();
		title.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
		titleBounds.top + titleBounds.height / 2.0f);
		title.setPosition(window.getSize().x / 2.0f, 100.f);
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < 5; i++)
		{
			Text option(menuoptions[i], font, menuItemSize);
			if (i == selectedOption)
			{
				option.setFillColor(selectedColor);
				option.setStyle(Text::Bold | Text::Underlined);
			}
			else
			{
				option.setFillColor(normalColor);
			}
			FloatRect optionBounds = option.getLocalBounds();
			option.setOrigin(optionBounds.left + optionBounds.width / 2.0f,
				optionBounds.top + optionBounds.height / 2.0f);
			option.setPosition(window.getSize().x / 2.0f,
				200.f + i * (menuItemSize + padding));

			window.draw(option);
		}
		Text instructions("Use UP/DOWN arrows to navigate, ENTER to select", font, 40);
		instructions.setFillColor(Color::Black);
		FloatRect instrBounds = instructions.getLocalBounds();
		instructions.setOrigin(instrBounds.left + instrBounds.width / 2.0f,
			instrBounds.top + instrBounds.height / 2.0f);
		instructions.setPosition(window.getSize().x / 2.0f,
			window.getSize().y - 50.f);
		window.draw(instructions);

	}
	void handleInput(Event& event)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Up)
				selectedOption = (selectedOption - 1 + 5) % 5;
			else if (event.key.code == Keyboard::Down)
				selectedOption = (selectedOption + 1) % 5;
			else if (event.key.code == Keyboard::Enter)
			{
				actionTaken = selectedOption;
				menuActive = false;
			}
			else if (event.key.code == Keyboard::Escape)
			{
				actionTaken = -1; // No option selected
				menuActive = false;
			}
		}
	}

	int run(RenderWindow& window)
	{
		menuActive = true;
		selectedOption = 0;
		actionTaken = -1;

		while (window.isOpen() && menuActive)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
					return -1;
				}
				handleInput(event);
			}

			displayMenu(window);
			window.display();
		}

		return actionTaken;
	}

	void displayLevelMenu(RenderWindow& window)
	{
		window.clear(Color::Black);

		// Title
		Text title("Select Level", font, 80);
		title.setFillColor(Color::Cyan);
		title.setStyle(Text::Bold);
		FloatRect titleBounds = title.getLocalBounds();
		title.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
			titleBounds.top + titleBounds.height / 2.0f);
		title.setPosition(window.getSize().x / 2.0f, 100.f);
		window.draw(background);
		window.draw(title);

		// Level options
		for (int i = 0; i < 4; i++)
		{
			Text option(levelOptions[i], font, menuItemSize);
			if (i == selectedLevel)
			{
				option.setFillColor(selectedColor);
				option.setStyle(Text::Bold | Text::Underlined);
			}
			else
			{
				option.setFillColor(normalColor);
			}

			FloatRect optionBounds = option.getLocalBounds();
			option.setOrigin(optionBounds.left + optionBounds.width / 2.0f,
				optionBounds.top + optionBounds.height / 2.0f);
			option.setPosition(window.getSize().x / 2.0f,
				200.f + i * (menuItemSize + padding));

			window.draw(option);
		}
		Text instructions("Use UP/DOWN arrows to navigate, ENTER to select, ESC to go back", font, 20);
		instructions.setFillColor(Color(200, 200, 200));
		FloatRect instrBounds = instructions.getLocalBounds();
		instructions.setOrigin(instrBounds.left + instrBounds.width / 2.0f,
			instrBounds.top + instrBounds.height / 2.0f);
		instructions.setPosition(window.getSize().x / 2.0f,
			window.getSize().y - 50.f);
		window.draw(instructions);
	}
	void handleLevelInput(Event& event)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Up)
				selectedLevel = (selectedLevel - 1 + 4) % 4;
			else if (event.key.code == Keyboard::Down)
				selectedLevel = (selectedLevel + 1) % 4;
			else if (event.key.code == Keyboard::Enter)
			{
				actionTaken = selectedLevel + 10; // Offset to distinguish from main menu options
				levelMenuActive = false;
			}
			else if (event.key.code == Keyboard::Escape)
			{
				levelMenuActive = false;
				menuActive = true; // Return to main menu
			}
		}
	}
	int runLevelMenu(RenderWindow& window)
	{
		levelMenuActive = true;
		selectedLevel = 0;
		actionTaken = -1;

		while (window.isOpen() && levelMenuActive)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
					return -1;
				}
				handleLevelInput(event);
			}

			displayLevelMenu(window);
			window.display();
		}

		return actionTaken;
	}
};
