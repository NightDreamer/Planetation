#include "Main.h"
#include "Game.h"
#include "Screen_Mainmenu.h"
#include "Screen_Ingame.h"
#include "Screen_How.h"
bool RUNNING = true;

int main()
{
	// init
	sf::ContextSettings cfg;
	cfg.antialiasingLevel	= 16;
	cfg.depthBits			= 0;
	cfg.majorVersion		= 2;
	cfg.minorVersion		= 0;
	cfg.stencilBits			= 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Planetation v1.0", sf::Style::Titlebar, cfg);
	window.setMouseCursorVisible(true);
	window.setVerticalSyncEnabled(true);

	sf::Image icon;
	icon.loadFromFile(".//data//textures//ingame//main_planet.png");

	window.setIcon(128, 128, icon.getPixelsPtr());

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_TEXTURE_2D);

	Vars vars;
	Game game;

	Screen_How how;
	how.game = &game;
	how.vars = &vars;
	Screen_Mainmenu mainmenu;
	mainmenu.game = &game;
	mainmenu.vars = &vars;
	mainmenu.screen_how = &how;
	Screen_Ingame ingame;
	ingame.game = &game;
	ingame.vars = &vars;

	game.screens.push_back(&mainmenu);
	game.screens.push_back(&ingame);

	game.setScreen(game.screens.at(0));

	std::cout << "init successfull" << std::endl;

	// game loop
	sf::Clock clock;

	while(vars.running)
	{
		sf::Time delta = clock.restart();

		sf::Event event;

		while(window.pollEvent(event))
		{
			;
		}

		glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		game.update((float)delta.asSeconds(), &window);
		game.render(&window);

		window.display();
	}

	window.close();


	return 0;
}