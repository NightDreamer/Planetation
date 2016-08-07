#pragma once
#include "Main.h"
class Planet
{
public:
	Planet(void);
	~Planet(void);

	void update(float);
	void render(sf::RenderWindow*);

	bool isAlive();

	void subLife(int);
	void subDefense(int);

	void addLife(int);
	void addDefense(int);

	void increaseRound();

	int getLife();
	int getDefense();
	int getRound();

private:
	int					life, defense, round;

	sf::Texture			mainplanet_tex, mainplanet_defense_tex;
	sf::Sprite			mainplanet_sprite, mainplanet_defense_sprite;
};

