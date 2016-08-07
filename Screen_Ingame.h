#pragma once
#include "Main.h"
#include "Game.h"
#include "AmmoManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "HUD.h"
class Screen_Ingame : public Screen
{
public:
	Screen_Ingame(void);
	~Screen_Ingame(void);

	void reset();
	void update(float, sf::RenderWindow*);
	void render(sf::RenderWindow*);

private:
	AmmoManager*		ammo_manager;
	EnemyManager*		enemy_manager;
	Player*				player;
	Planet*				planet;
	HUD*				hud;

	sf::Music			bgm_ingame;

	sf::Texture			ingamebg_tex;
	sf::Sprite			ingamebg_sprite;
};

