#include "Planet.h"


Planet::Planet(void)
{
	life = 100;
	defense = 100;
	round = 0;

	mainplanet_tex.loadFromFile(".//data//textures//ingame//main_planet.png");
	mainplanet_tex.setSmooth(true);

	mainplanet_sprite.setTexture(mainplanet_tex);
	mainplanet_sprite.setScale(1.0f, 1.0f);
	mainplanet_sprite.setPosition(400.0f - mainplanet_sprite.getGlobalBounds().width/2, 300.0f - mainplanet_sprite.getGlobalBounds().height/2);

	mainplanet_defense_tex.loadFromFile(".//data//textures//ingame//main_planet_defense2.png");
	mainplanet_defense_tex.setSmooth(true);

	mainplanet_defense_sprite.setTexture(mainplanet_defense_tex);
	mainplanet_defense_sprite.setScale(1.25f, 1.25f);
	mainplanet_defense_sprite.setPosition(400.0f - mainplanet_defense_sprite.getGlobalBounds().width/2, 300.0f - mainplanet_defense_sprite.getGlobalBounds().height/2);

	mainplanet_defense_sprite.setColor(sf::Color(255, 255, 255, 255));
}


Planet::~Planet(void)
{
}

void Planet::update(float delta)
{
	mainplanet_defense_sprite.setColor(sf::Color(255, 255, 255, (int)(255/100*defense)));
}

void Planet::render(sf::RenderWindow* window)
{
	window->draw(mainplanet_sprite);
	window->draw(mainplanet_defense_sprite);
}

bool Planet::isAlive()
{
	return (life > 0);
}

void Planet::subLife(int value)
{
	life -= value;
	if(life < 0) life = 0;
}

void Planet::subDefense(int value)
{
	defense -= value;
	if(defense < 0) defense = 0;
}

void Planet::increaseRound()
{
	round++;
}

void Planet::addLife(int value)
{
	life += value;
	if(life > 100) life = 100;
}

void Planet::addDefense(int value)
{
	defense += value;
	if(defense > 100) defense = 100;
}

int Planet::getLife()
{
	return life;
}

int Planet::getDefense()
{
	return defense;
}

int Planet::getRound()
{
	return round;
}
