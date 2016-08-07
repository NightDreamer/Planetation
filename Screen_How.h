#pragma once
#include "Main.h"
#include "Game.h"
class Screen_How : public Screen
{
public:
	Screen_How(void);
	~Screen_How(void);

	void update(float, sf::RenderWindow*);
	void render(sf::RenderWindow*);

private:
	sf::Rect<float>		back_bounds;
	bool				back_hovered;

	sf::SoundBuffer		sound_buffer;
	sf::Sound			hover;

	sf::Texture			bg_tex, back_inactive_tex, back_active_tex;
	sf::Sprite			bg_sprite, back_inactive_sprite, back_active_sprite;
};

