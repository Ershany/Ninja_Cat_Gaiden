#include "EnterPortal.h"
#include "Defs.h"

#include <iostream>

EnterPortal::EnterPortal(sf::Vector2f &position, GamestateManager &gsm, Player *player)
	: InteractableObject(position, gsm), CollectibleObject(position, sf::Vector2u(32, 32), player)
{
	this->type = InteractableObject::Type::EnterPortal;

	// Tweakable Variables
	this->size.x = 37;
	this->size.y = 80;
	this->maxGrabLength = 60.0f * 60.0f; // The distance (radius) at which the player can grab the object (Note: Square it since the calucation doesnt sqrt)
}

EnterPortal::~EnterPortal() {

}

void EnterPortal::update(const sf::Time &deltaTime) {
	// Check if the player is hitting 'f'
	if (CollectibleObject::isPlayerTakingObject()) {
		action(deltaTime);
	}
}

void EnterPortal::action(const sf::Time &deltaTime) {
	player->transitioningToNextLevel = true;
}