#include "EnterPortal.h"
#include "Defs.h"

#include <iostream>

EnterPortal::EnterPortal(sf::Vector2f &position, GamestateManager &gsm, Player *player)
	: InteractableObject(position, gsm), CollectibleObject(position, sf::Vector2u(32, 32), player)
{
	this->type = InteractableObject::Type::EnterPortal;

	// Tweakable Variables
	this->maxGrabLength = 40.0f * 40.0f; // The distance (radius) at which the player can grab the object (Note: Square it since the calucation doesnt sqrt)
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

}