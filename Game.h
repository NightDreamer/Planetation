#pragma once
#include "Main.h"

class Screen;

class Game
{
public:
	Game(void);
	~Game(void);

	void setScreen(Screen* screen);
	void update(float, sf::RenderWindow*);
	void render(sf::RenderWindow*);

private:
	Screen*					actual_screen;

public:
	std::vector<Screen*>		screens;
};

class Screen
{
public:
	virtual void update(float delta, sf::RenderWindow*){};
	virtual void render(sf::RenderWindow* window){};
	virtual void reset(){};

public:
	Vars*		vars;
	Game*		game;
	int			id;
};

