#include "CollectibleObject.h"

#include "Defs.h"

CollectibleObject::CollectibleObject(sf::Vector2f objectPosition, sf::Vector2u size, Player *player) {
	this->objectPosition = objectPosition;
	this->size = size;
	this->player = player;
}

bool CollectibleObject::isPlayerTakingObject() {
	// Check if the player is hitting 'f'
	if (player->fHeld) {
		// Check if the player is close enough to grab the object
		if (squaredLength((objectPosition + sf::Vector2f(size.x * 0.5f, size.y * 0.5f)) - (player->position + sf::Vector2f(player->size.x * 0.5f, player->size.y * 0.5f))) <= maxGrabLength) {
			return true;
		}
	}

	return false;
}