#include "Screen_Ingame.h"


Screen_Ingame::Screen_Ingame(void)
{
	id = 1;

	planet = new Planet();

	ammo_manager = new AmmoManager();
	ammo_manager->setPlanet(planet);

	enemy_manager = new EnemyManager();
	enemy_manager->setAmmoManager(ammo_manager);

	player = new Player();
	player->setAmmoManager(ammo_manager);

	hud = new HUD();
	hud->setPlanet(planet);

	bgm_ingame.openFromFile(".//data//bgm//bgm_ingame.ogg");
	bgm_ingame.setLoop(true);
	bgm_ingame.setVolume(80.0f);

	ingamebg_tex.loadFromFile(".//data//textures//ingame//ingame_bg.png");
	ingamebg_tex.setSmooth(true);

	ingamebg_sprite.setTexture(ingamebg_tex);
	ingamebg_sprite.setScale(0.78125f, 0.5859375f);
	ingamebg_sprite.setPosition(0.0f, 0.0f);
}


Screen_Ingame::~Screen_Ingame(void)
{
	delete hud;
	delete player;
	delete enemy_manager;
	delete ammo_manager;
	delete planet;

	if(bgm_ingame.getStatus() == sf::Music::Playing)
	{
		bgm_ingame.stop();
	}
}

void Screen_Ingame::reset()
{
	delete hud;
	delete player;
	delete enemy_manager;
	delete ammo_manager;
	delete planet;

	planet = new Planet();

	ammo_manager = new AmmoManager();
	ammo_manager->setPlanet(planet);

	enemy_manager = new EnemyManager();
	enemy_manager->setAmmoManager(ammo_manager);

	player = new Player();
	player->setAmmoManager(ammo_manager);

	hud = new HUD();
	hud->setPlanet(planet);
}

void Screen_Ingame::update(float delta, sf::RenderWindow* window)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || planet->getLife() == 0)
	{
		bgm_ingame.stop();
		game->setScreen(game->screens.at(0));
		return;
	}

	// music
	if(bgm_ingame.getStatus() != sf::Music::Playing)
	{
		bgm_ingame.play();
	}

	// ingame
	planet->update(delta);
	player->update(delta, window);

	enemy_manager->update(delta);

	ammo_manager->update(delta);

	// energy
	sf::Rect<float> p_bounds = player->getBounds();
	for(auto i = enemy_manager->energies.begin(); i != enemy_manager->energies.end();)
	{
		if(p_bounds.contains(i->x, i->y))
		{
			planet->addDefense(i->energy);
			i = enemy_manager->energies.erase(i);
		}else
		{
			i++;
		}
	}

	// hud
	hud->update(delta);
}

void Screen_Ingame::render(sf::RenderWindow* window)
{
	// bg
	window->draw(ingamebg_sprite);

	// ingame
	planet->render(window);
	player->render(window);

	enemy_manager->render(window);

	ammo_manager->render(window);

	// hud
	hud->render(window);
}
