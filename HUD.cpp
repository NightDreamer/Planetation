#include "HUD.h"


HUD::HUD(void)
{
	font.loadFromFile(".//data//font//segoescb.ttf");
	text.setFont(font);

	player_life_tex.loadFromFile(".//data//textures//ingame//res_life.png");
	player_life_tex.setSmooth(true);

	player_life_sprite.setTexture(player_life_tex);
	player_life_sprite.setScale(0.5f, 0.5f);
	player_life_sprite.setPosition(5.0f, 5.0f);

	planet_defense_tex.loadFromFile(".//data//textures//ingame//res_defense.png");
	planet_defense_tex.setSmooth(true);

	planet_defense_sprite.setTexture(planet_defense_tex);
	planet_defense_sprite.setScale(0.5f, 0.5f);
	planet_defense_sprite.setPosition(700.0f, 5.0f);
}


HUD::~HUD(void)
{
}

void HUD::update(float delta)
{
	;
}

void HUD::render(sf::RenderWindow* window)
{
	window->draw(player_life_sprite);
	window->draw(planet_defense_sprite);

	text.setString(std::to_string(planet->getLife()));
	text.setCharacterSize(30);
	text.setPosition(38.0f, 0.0f);

	window->draw(text);

	text.setString(std::to_string(planet->getDefense()));
	text.setCharacterSize(30);
	text.setPosition(732.0f, 0.0f);

	window->draw(text);

	text.setString("Round "+std::to_string(planet->getRound()));
	text.setCharacterSize(32);
	text.setPosition(300.0f, 0.0f);

	window->draw(text);
}

void HUD::setPlanet(Planet* planet)
{
	this->planet = planet;
}