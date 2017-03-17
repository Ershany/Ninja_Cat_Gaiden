#include "ContainerObj.h"
#include "Defs.h"

#include <iostream>

ContainerObj::ContainerObj(sf::Vector2f &position, GamestateManager &gsm, Player *player)
	: InteractableObject(position, gsm), CollectibleObject(position, sf::Vector2u(32, 32), player)
{
	this->type = InteractableObject::Type::Container;

	// Tweakable Variables
	this->maxGrabLength = 40.0f * 40.0f; // The distance (radius) at which the player can grab the object (Note: Square it since the calucation doesnt sqrt)
}

ContainerObj::~ContainerObj() {

}

void ContainerObj::update(const sf::Time &deltaTime) {
	// Check if the player is hitting 'f'
	if (CollectibleObject::isPlayerTakingObject()) {
		action(deltaTime);
	}
}

void ContainerObj::action(const sf::Time &deltaTime) {
	shouldRemove = true;
	// Add a container to the player's inventory
	player->inventory.numContainer++;
}