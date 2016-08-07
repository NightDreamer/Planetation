#pragma once
#include "Main.h"
#include "Game.h"
#include "Screen_How.h"
class Screen_Mainmenu : public Screen
{
public:
	Screen_Mainmenu(void);
	~Screen_Mainmenu(void);

	void update(float, sf::RenderWindow*);
	void render(sf::RenderWindow*);

private:
	sf::Rect<float>		start_bounds, how_bounds, exit_bounds;
	bool				start_hovered, how_hovered, exit_hovered;

	sf::SoundBuffer		sound_buffer;
	sf::Sound			hover_sfx;
	sf::Music			bgm;

	sf::Texture			bg_tex, start_active_tex, start_inactive_tex, how_active_tex, how_inactive_tex, exit_active_tex, exit_inactive_tex;
	sf::Sprite			bg_sprite, start_active_sprite, start_inactive_sprite, how_active_sprite, how_inactive_sprite, exit_active_sprite, exit_inactive_sprite;

public:
	Screen_How*			screen_how;
};

