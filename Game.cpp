#include "Game.h"


Game::Game(void)
{
	actual_screen = NULL;
}


Game::~Game(void)
{
	actual_screen = NULL;
}

void Game::setScreen(Screen* screen)
{
	actual_screen = screen;
}

void Game::update(float delta, sf::RenderWindow* window)
{
	if(actual_screen) actual_screen->update(delta, window);
}

void Game::render(sf::RenderWindow* window)
{
	if(actual_screen) actual_screen->render(window);
}