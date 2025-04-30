#pragma once
class Characters
{
	int** Active;
	int hp;
	int hits;
	int s_position_x, s_position_y;
	int f_position_x, f_position_y;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f scaleFactor = { 1.0f, 1.0f };
public:
	virtual void move();
	virtual void attack();
	virtual void boost();
};
class Sonic :public Characters
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
	void speedrun();

};
class Knuckles : public Characters
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
	void breakwall();
};
class Tails : public Characters
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
	void fly();
};
