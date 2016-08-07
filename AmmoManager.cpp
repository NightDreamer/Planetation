#include "AmmoManager.h"

AmmoManager::AmmoManager(void)
{
	sound_buffer.loadFromFile(".//data//sfx//shot.wav");

	sfx_shot.setBuffer(sound_buffer);
	sfx_shot.setVolume(100.0f);

	window_bounds.top	 = 0.0f;
	window_bounds.left	 = 0.0f;
	window_bounds.width	 = 800.0f;
	window_bounds.height = 600.0f;

	playershot_tex.loadFromFile(".//data//textures//ingame//blue_fire.png");
	playershot_tex.setSmooth(true);

	playershot_sprite.setTexture(playershot_tex);
	playershot_sprite.setOrigin((float)playershot_tex.getSize().x, (float)playershot_tex.getSize().y);
	playershot_sprite.scale(0.15f, 0.9f);

	enemyshot_tex.loadFromFile(".//data//textures//ingame//red_fire.png");
	enemyshot_tex.setSmooth(true);

	enemyshot_sprite.setTexture(enemyshot_tex);
	enemyshot_sprite.setOrigin((float)enemyshot_tex.getSize().x, (float)enemyshot_tex.getSize().y);
	enemyshot_sprite.scale(0.15f, 0.9f);
}


AmmoManager::~AmmoManager(void)
{
	if(sfx_shot.Playing)
	{
		sfx_shot.stop();
	}
}

void AmmoManager::setPlanet(Planet* planet)
{
	this->planet = planet;
}

void AmmoManager::update(float delta)
{
	if(!shots.empty())
	{
		for(auto i = shots.begin(); i != shots.end();)
		{
			if(!window_bounds.contains(i->x, i->y))
			{
				i = shots.erase(i);
			}
			else
			{
				// ammo destroys planet
				sf::Vector2f dir(400 - i->x, 300 - i->y);
				float length = sqrtf( powf(dir.x, 2.0f) + powf(dir.y, 2.0f) );

				if(length <= 90.0f)
				{
					if(planet->getDefense() > 0)
					{
						planet->subDefense(i->dmg);
					}
					else
					{
						planet->subLife(i->dmg);
					}

					i = shots.erase(i);
				}
				else
				{
					// ammo velocity
					i->x += cos(i->angle * PI / 180.0f)*delta*255.0f;
					i->y += sin(i->angle * PI / 180.0f)*delta*255.0f;

					i++;
				}
			}
		}
	}
}

void AmmoManager::render(sf::RenderWindow* window)
{
	if(!shots.empty())
	{
		for(auto i = shots.begin(); i != shots.end(); i++)
		{
			if(i->id == -2)
			{
				playershot_sprite.setPosition(i->x, i->y);
				playershot_sprite.setRotation(i->angle + 90.0f);
				window->draw(playershot_sprite);
			}
			else
			{
				enemyshot_sprite.setPosition(i->x, i->y);
				enemyshot_sprite.setRotation(i->angle + 90.0f);
				window->draw(enemyshot_sprite);
			}
			
		}
	}
}

Planet* AmmoManager::getPlanet()
{
	return planet;
}

void AmmoManager::addShot(float x, float y, float angle, int dmg, int id)
{
	sfx_shot.play();
	shots.push_back(Ammo(x, y, angle, dmg, id));
}

std::vector<Ammo>* AmmoManager::getShots()
{
	return &shots;
}
