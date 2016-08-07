#include "Player.h"
bool fire = false, first = true;

Player::Player(void)
{
	id = -2;
	dmg = 20;

	ship_tex.loadFromFile(".//data//textures//ingame//player_ship.png");
	ship_tex.setSmooth(true);

	ship_sprite.setTexture(ship_tex);
	ship_sprite.setScale(0.5f, 0.5f);
	ship_sprite.setPosition(400.0f - ship_sprite.getGlobalBounds().width/2, 300.0f - ship_sprite.getGlobalBounds().height/2);
	ship_sprite.setOrigin(ship_sprite.getLocalBounds().width/2, ship_sprite.getLocalBounds().height/2);
	ship_sprite.setRotation(0.0f);

	mouse_click.x = mouse_click.y = 0;
}


Player::~Player(void)
{
}

void Player::setAmmoManager(AmmoManager* manager)
{
	this->ammo_manager = manager;
}

void Player::update(float delta, sf::RenderWindow* window)
{
	sf::Vector2f pos_ship = ship_sprite.getPosition();
	sf::Vector2i pos_cursor = sf::Mouse::getPosition(*window);

	float dx = pos_cursor.x - pos_ship.x;
	float dy = pos_cursor.y - pos_ship.y;

	float angle_degrees = (atan2(dy, dx)) * 180.0f / PI;

	ship_sprite.setRotation(angle_degrees + 90.0f);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		if(!fire)
		{
			ammo_manager->addShot(pos_ship.x, pos_ship.y, angle_degrees, dmg, id);
			fire = true;
		}
	}
	else
	{
		fire = false;
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if(!first)
		{
			mouse_click.x = sf::Mouse::getPosition(*window).x;
			mouse_click.y = sf::Mouse::getPosition(*window).y;
		}
	}else first = false;

	if(mouse_click.x != 0 || mouse_click.y != 0)
	{
		float dx = mouse_click.x - pos_ship.x;
		float dy = mouse_click.y - pos_ship.y;

		float angle_radians = (std::atan2(dy, dx));

		ship_sprite.setPosition( ship_sprite.getPosition().x + cosf(angle_radians)*delta*150.0f , ship_sprite.getPosition().y + sinf(angle_radians)*delta*150.0f );
	
		float length = sqrt( pow(dx,2) + pow(dy,2) );
		if(length < 1.0f && length > -1.0f)
		{
			mouse_click.x = 0;
			mouse_click.y = 0;
		}
	}


}

void Player::render(sf::RenderWindow* window)
{
	window->draw(ship_sprite);
}

sf::Rect<float> Player::getBounds()
{
	return ship_sprite.getGlobalBounds();
}
