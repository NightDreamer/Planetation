#include "EnemyManager.h"

EnemyManager::EnemyManager(void)
{
	srand((unsigned)time(0));

	enemy_tex.loadFromFile(".//data//textures//ingame//player_ship.png");
	enemy_tex.setSmooth(true);

	enemy_sprite.setTexture(enemy_tex);
	enemy_sprite.setScale(0.5f, 0.5f);
	enemy_sprite.setOrigin(enemy_sprite.getLocalBounds().width/2, enemy_sprite.getLocalBounds().height/2);
	enemy_sprite.setColor(sf::Color(255, 0, 100, 255));

	energy_tex.loadFromFile(".//data//textures//ingame//energy.png");
	energy_tex.setSmooth(true);

	energy_sprite.setTexture(energy_tex);
	energy_sprite.setScale(0.5f, 0.5f);
	energy_sprite.setOrigin(energy_sprite.getLocalBounds().width/2, energy_sprite.getLocalBounds().height/2);
}


EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::setAmmoManager(AmmoManager* ammo_manager)
{
	this->ammo_manager = ammo_manager;
}

void EnemyManager::update(float delta)
{
	if(enemies.empty())
	{
		ammo_manager->getPlanet()->increaseRound();

		while( enemies.size() < (unsigned)(4+ammo_manager->getPlanet()->getRound()) )
		{
			float spawn_angle	= ( (float)rand()/(float)RAND_MAX ) * 360.0f;

			for(auto i = enemies.begin(); i != enemies.end();)
			{
				if( (i->spawned_angle+10 > spawn_angle) && (i->spawned_angle-10 < spawn_angle) )
				{
					spawn_angle += 15;
				}
				else
				{
					i++;
				}
			}

			float x	= 400 + (500 * cosf(spawn_angle * PI / 180.0f));
			float y	= 300 + (500 * sinf(spawn_angle * PI / 180.0f));

			float dx = 400 - x;
			float dy = 300 - y;

			float angle = atan2(dy, dx);

			int rndm_shoottime = 1 + (rand() % 5);
			int health = 80;
			int lvl = 1;

			if(ammo_manager->getPlanet()->getRound() >= 2)
			{
				lvl += (rand() % 2);
				if(lvl == 2) health += 20;
			}

			enemies.push_back(Enemy(x, y, angle, spawn_angle, health, 2, rndm_shoottime, lvl, enemies.size()));
		}

		return;
	}
	else
	{
		for(auto i = enemies.begin(); i != enemies.end();)
		{
			// is dead
			if(i->life <= 0)
			{
				energies.push_back(Energy(i->x, i->y, 5));
				i = enemies.erase(i);
			}
			else
			{
				// enemies & player shots
				enemy_sprite.setPosition(i->x, i->y);
				enemy_sprite.setRotation((i->angle * 180.0f / PI) + 90.0f);
				sf::Rect<float> bounds = enemy_sprite.getGlobalBounds();

				for(auto j = ammo_manager->getShots()->begin(); j != ammo_manager->getShots()->end();)
				{
					if(bounds.contains(j->x, j->y) && (j->id != i->id))
					{
						i->life -= j->dmg;
						j = ammo_manager->getShots()->erase(j);
					}
					else
					{
						j++;
					}
				}

				// fly around
				sf::Vector2f dir( 400 - i->x, 300 - i->y );
				float length = sqrtf( powf(dir.x, 2.0f) + powf(dir.y, 2.0f) );  

				if(i->lvl == 1 && length > 200.0f)
				{
					i->x += delta*150.0f*cosf(i->angle);
					i->y += delta*150.0f*sinf(i->angle);
				}
				else if(i->lvl >= 2 && length > 250.0f)
				{
					i->x += delta*150.0f*cosf(i->angle);
					i->y += delta*150.0f*sinf(i->angle);
				}

				// shoot
				if(i->time.asSeconds() > i->shoot_time)
				{
					i->time = sf::Time::Zero;
					ammo_manager->addShot(i->x, i->y, i->angle * 180.0f / PI, i->dmg, i->id);
				}
				else
				{
					i->time += i->clock.restart();
				}

				i++;
			}
		}
	}
}

void EnemyManager::render(sf::RenderWindow* window)
{
	for(auto i = energies.begin(); i != energies.end(); i++)
	{
		energy_sprite.setPosition(i->x, i->y);
		window->draw(energy_sprite);
	}

	for(auto i = enemies.begin(); i != enemies.end(); i++)
	{
		int lvl = i->lvl;

		if(lvl == 1)
		{
			enemy_sprite.setColor(sf::Color(255, 0, 0, 255));
		}
		else if(lvl == 2)
		{
			enemy_sprite.setColor(sf::Color(0, 0, 255, 255));
		}

		enemy_sprite.setPosition(i->x, i->y);
		enemy_sprite.setRotation((i->angle * 180.0f / PI) + 90.0f);
		window->draw(enemy_sprite);
	}
}