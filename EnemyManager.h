#pragma once
#include <ctime>
#include "Main.h"
#include "AmmoManager.h"
struct Enemy
{
	Enemy(float x, float y, float angle, float spawned_angle, int life, int dmg, int shoot_time, int lvl, int id)
	{ 
		this->x = x; this->y = y; this->angle = angle; this->spawned_angle = spawned_angle; this->life = life; this->dmg = dmg; this->shoot_time = shoot_time; this->lvl = lvl; this->id = id; 
		shoot_time = rand();
		time = sf::Time::Zero;
	};

	float x, y, angle, spawned_angle;
	int id, life, dmg, shoot_time, lvl;

	sf::Clock clock;
	sf::Time time;
};

struct Energy
{
	Energy(float x, float y, int energy)
	{
		this->x = x; this->y = y; this->energy = energy;
	}

	float x, y;
	int energy;
};

class EnemyManager
{
public:
	EnemyManager(void);
	~EnemyManager(void);

	void setAmmoManager(AmmoManager*);
	void update(float);
	void render(sf::RenderWindow*);

private:
	std::vector<Enemy>	enemies;

	sf::Texture			enemy_tex, energy_tex;
	sf::Sprite			enemy_sprite, energy_sprite;

	AmmoManager*		ammo_manager;

public:
	std::vector<Energy> energies;
};

