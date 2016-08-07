#pragma once
#include "Main.h"
#include "Planet.h"
struct Ammo
{
	Ammo(float x, float y, float angle, int dmg, int id){ this->x = x; this->y = y; this->angle = angle; this->dmg = dmg; this->id = id; };

	float x, y, angle;
	int id, dmg;
};

class AmmoManager
{
public:
	AmmoManager(void);
	~AmmoManager(void);

	void setPlanet(Planet*);
	void update(float);
	void render(sf::RenderWindow*);

	Planet* getPlanet();

	void addShot(float, float, float, int, int);
	std::vector<Ammo>* getShots();

private:
	Planet*				planet;

	sf::SoundBuffer		sound_buffer;
	sf::Sound			sfx_shot;

	sf::Rect<float>		window_bounds;
	std::vector<Ammo>	shots;

	sf::Texture			playershot_tex, enemyshot_tex;
	sf::Sprite			playershot_sprite, enemyshot_sprite;
};

