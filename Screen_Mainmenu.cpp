#include "Screen_Mainmenu.h"
bool first_esc = true;

Screen_Mainmenu::Screen_Mainmenu(void)
{
	id = 0;

	sound_buffer.loadFromFile(".//data//sfx//select.wav");

	hover_sfx.setBuffer(sound_buffer);
	hover_sfx.setVolume(50.0f);

	bgm.openFromFile(".//data//bgm//bgm_mainmenu.ogg");
	bgm.setLoop(true);
	bgm.setVolume(50);

	// bools
	start_hovered = how_hovered = exit_hovered = false;

	// buttons bounds
	start_bounds.left	= 92.0f;
	start_bounds.top	= 251.0f;
	start_bounds.width	= 92.0f;
	start_bounds.height	= 25.0f;

	how_bounds.left		= 34.0f;
	how_bounds.top		= 354.0f;
	how_bounds.width	= 198.0f;
	how_bounds.height	= 25.0f;

	exit_bounds.left	= 658.0f;
	exit_bounds.top		= 514.0f;
	exit_bounds.width	= 70.0f;
	exit_bounds.height	= 25.0f;


	// Background
	bg_tex.loadFromFile(".//data//textures//mainmenu//mainmenu_bg.png");
	bg_tex.setSmooth(true);

	bg_sprite.setTexture(bg_tex);
	bg_sprite.setPosition(0.0f, 0.0f);
	bg_sprite.setScale(0.78125f, 0.5859375f);


	// START button
	start_active_tex.loadFromFile(".//data//textures//mainmenu//mainmenu_start_active.png");
	start_active_tex.setSmooth(true);

	start_active_sprite.setTexture(start_active_tex);
	start_active_sprite.setPosition(0.0f, 0.0f);
	start_active_sprite.setScale(0.78125f, 0.5859375f);

	start_inactive_tex.loadFromFile(".//data//textures//mainmenu//mainmenu_start_inactive.png");
	start_inactive_tex.setSmooth(true);

	start_inactive_sprite.setTexture(start_inactive_tex);
	start_inactive_sprite.setPosition(0.0f, 0.0f);
	start_inactive_sprite.setScale(0.78125f, 0.5859375f);

	// HOW TO PLAY button
	how_active_tex.loadFromFile(".//data//textures//mainmenu//mainmenu_how_active.png");
	how_active_tex.setSmooth(true);

	how_active_sprite.setTexture(how_active_tex);
	how_active_sprite.setPosition(0.0f, 0.0f);
	how_active_sprite.setScale(0.78125f, 0.5859375f);

	how_inactive_tex.loadFromFile(".//data//textures//mainmenu//mainmenu_how_inactive.png");
	how_inactive_tex.setSmooth(true);

	how_inactive_sprite.setTexture(how_inactive_tex);
	how_inactive_sprite.setPosition(0.0f, 0.0f);
	how_inactive_sprite.setScale(0.78125f, 0.5859375f);

	// EXIT button
	exit_active_tex.loadFromFile(".//data//textures//mainmenu//mainmenu_exit_active.png");
	exit_active_tex.setSmooth(true);

	exit_active_sprite.setTexture(exit_active_tex);
	exit_active_sprite.setPosition(0.0f, 0.0f);
	exit_active_sprite.setScale(0.78125f, 0.5859375f);

	exit_inactive_tex.loadFromFile(".//data//textures//mainmenu//mainmenu_exit_inactive.png");
	exit_inactive_tex.setSmooth(true);

	exit_inactive_sprite.setTexture(exit_inactive_tex);
	exit_inactive_sprite.setPosition(0.0f, 0.0f);
	exit_inactive_sprite.setScale(0.78125f, 0.5859375f);
}


Screen_Mainmenu::~Screen_Mainmenu(void)
{
	if(bgm.getStatus() == sf::Music::Playing)
	{
		bgm.stop();
	}
}

void Screen_Mainmenu::update(float delta, sf::RenderWindow* window)
{
	// music
	if(bgm.getStatus() != sf::Music::Playing)
	{
		bgm.play();
	}

	if(vars->howtoplay)
	{
		screen_how->update(delta, window);
		return;
	}

	float x = (float)sf::Mouse::getPosition(*window).x;
	float y = (float)sf::Mouse::getPosition(*window).y;

	if(start_bounds.contains(x, y))
	{
		if(!start_hovered)
		{
			start_hovered = true;
			hover_sfx.play();
		}
	}else start_hovered = false;

	if(how_bounds.contains(x, y))
	{
		if(!how_hovered)
		{
			how_hovered = true;
			hover_sfx.play();
		}
	}else how_hovered = false;

	if(exit_bounds.contains(x, y))
	{
		if(!exit_hovered)
		{
			exit_hovered = true;
			hover_sfx.play();
		}
	}else exit_hovered = false;


	if(start_hovered)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			bgm.stop();
			hover_sfx.stop();
			first_esc = true;
			game->screens.at(1)->reset();
			game->setScreen(game->screens.at(1));
			return;
		}
	}
	else if(how_hovered)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			vars->howtoplay = true;
		}
	}
	else if(exit_hovered)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			vars->running = false;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if(!first_esc)
		{
			vars->running = false;
		}
	}else first_esc = false;
}

void Screen_Mainmenu::render(sf::RenderWindow* window)
{
	if(vars->howtoplay)
	{
		screen_how->render(window);
		return;
	}

	window->draw(bg_sprite);

	if(start_hovered)
	{
		window->draw(start_active_sprite);
	}
	else if(how_hovered)
	{
		window->draw(how_active_sprite);
	}
	else if(exit_hovered)
	{
		window->draw(exit_active_sprite);
	}

	window->draw(start_inactive_sprite);
	window->draw(how_inactive_sprite);
	window->draw(exit_inactive_sprite);
}
