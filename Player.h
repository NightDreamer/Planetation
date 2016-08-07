#pragma once
#include "Main.h"
#include "AmmoManager.h"
class Player
{
public:
	Player(void);
	~Player(void);

	void setAmmoManager(AmmoManager*);
	void update(float, sf::RenderWindow*);
	void render(sf::RenderWindow*);

	sf::Rect<float> getBounds();

private:
	int					id, dmg;

	sf::Texture			ship_tex;
	sf::Sprite			ship_sprite;
	sf::Vector2i		mouse_click;

	AmmoManager*		ammo_manager;
};

