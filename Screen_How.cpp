#include "Screen_How.h"

Screen_How::Screen_How(void)
{
	back_hovered = false;

	sound_buffer.loadFromFile(".//data//sfx//select.wav");

	hover.setBuffer(sound_buffer);
	hover.setVolume(50.0f);

	back_bounds.top		= 248.0f;
	back_bounds.left	= 771.0f;
	back_bounds.width	= 29.0f;
	back_bounds.height	= 87.0f;

	bg_tex.loadFromFile(".//data//textures//howtoplay//howtoplay_menu.png");
	bg_tex.setSmooth(true);

	bg_sprite.setTexture(bg_tex);
	bg_sprite.setPosition(0.0f, 0.0f);
	bg_sprite.setScale(0.78125f, 0.5859375f);

	back_inactive_tex.loadFromFile(".//data//textures//howtoplay//howtoplay_menu_backINACTIVE.png");
	back_inactive_tex.setSmooth(true);

	back_inactive_sprite.setTexture(back_inactive_tex);
	back_inactive_sprite.setPosition(0.0f, 0.0f);
	back_inactive_sprite.setScale(0.78125f, 0.5859375f);

	back_active_tex.loadFromFile(".//data//textures//howtoplay//howtoplay_menu_backACTIVE.png");
	back_active_tex.setSmooth(true);

	back_active_sprite.setTexture(back_active_tex);
	back_active_sprite.setPosition(0.0f, 0.0f);
	back_active_sprite.setScale(0.78125f, 0.5859375f);
}


Screen_How::~Screen_How(void)
{
}

void Screen_How::update(float delta, sf::RenderWindow* window)
{
	float x = (float)sf::Mouse::getPosition(*window).x;
	float y = (float)sf::Mouse::getPosition(*window).y;

	if(back_bounds.contains(x, y))
	{
		if(!back_hovered)
		{
			hover.play();
			back_hovered = true;
		}
	}else back_hovered = false;

	if(back_hovered)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			vars->howtoplay = false;
		}
	}
}

void Screen_How::render(sf::RenderWindow* window)
{
	window->draw(bg_sprite);

	if(back_hovered)
	{
		window->draw(back_active_sprite);
	}

	window->draw(back_inactive_sprite);
}
