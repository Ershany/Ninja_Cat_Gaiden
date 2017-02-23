#include "Player.h"
#include "GamestateManager.h"

#include <iostream>

Player::Player(sf::Vector2f &pos, GamestateManager &gsm) 
	: gsm(gsm)
{
	this->position = pos;
	this->size.x = 56;
	this->size.y = 68;
}

Player::~Player() {

}

void Player::update(const sf::Time &deltaTime) {
	// Make sure a gamestate is currently being played, log it if there is no gamestate on the stack
	if (gsm.getCurrentState() == NULL) {
		std::cout << "Player Update Cancelled: No Gamestate On The Stack" << std::endl;
		return;
	}

	position.x += deltaTime.asSeconds() * 50.5f;
	position.y += deltaTime.asSeconds() * 50.5f;

	// Update the sprites position (screen position)
	sprite.setPosition(position - gsm.getCurrentState()->getTilemap()->getOffset());
}

sf::Vector2u Player::getSize() {
	return size;
}