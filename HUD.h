#pragma once
#include "Main.h"
#include "Planet.h"
class HUD
{
public:
	HUD(void);
	~HUD(void);

	void update(float);
	void render(sf::RenderWindow*);

	void setPlanet(Planet*);

private:
	Planet*				planet;

	sf::Font			font;
	sf::Text			text;

	sf::Texture			player_life_tex, planet_defense_tex;
	sf::Sprite			player_life_sprite, planet_defense_sprite;
};

