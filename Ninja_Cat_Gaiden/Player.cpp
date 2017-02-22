#include "Player.h"

Player::Player(sf::Vector2f &pos, Tilemap &map) 
	: tilemap(map)
{
	this->position = pos;
	this->size.x = 56;
	this->size.y = 68;
}

Player::~Player() {

}

void Player::update(const sf::Time &deltaTime) {
	position.x += deltaTime.asSeconds() * 50.5f;
	position.y += deltaTime.asSeconds() * 50.5f;

	// Update the sprites position (screen position)
	sprite.setPosition(position - tilemap.getOffset());
}

sf::Vector2u Player::getSize() {
	return size;
}