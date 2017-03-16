#include "Hideable.h"
#include "Defs.h"

#include <iostream>

Hideable::Hideable(sf::Vector2f &position, GamestateManager &gsm, Player *player)
	: InteractableObject(position, gsm)
{
	this->type = InteractableObject::Type::Hideable;
	this->playerInside = false;
	this->player = player;
	this->size.x = 78; this->size.y = 76;
	this->currentEnterExitCooldown = sf::milliseconds(0);

	// Tweakable Variables
	this->maxHideLength = 38.0f * 38.0f; // The distance at which the player can be from the hideable in order to hide (Note: Square it since the calucation doesnt sqrt)
	this->enterExitCooldown = sf::milliseconds(150);
}

Hideable::~Hideable() {

}

void Hideable::update(const sf::Time &deltaTime) {
	currentEnterExitCooldown += deltaTime;

	// Check if the player is inside
	if (playerInside) {
		player->position = position + sf::Vector2f(11.0f, 9.0f);
	}

	// Check if the player is hitting 'f'
	if (player->fHeld) {
		// Check if the player is close enough to the object to hide in it
		if (squaredLength((position + sf::Vector2f(size.x * 0.5f, size.y * 0.5f)) - (player->position + sf::Vector2f(player->size.x * 0.5f, player->size.y * 0.5f))) <= maxHideLength) {
			// The player is entering/exiting the hideble object
			if (currentEnterExitCooldown >= enterExitCooldown) {
				action(deltaTime);
			}
		}
	}
}

// Is called when the player is entering/exiting the hideable object
void Hideable::action(const sf::Time &deltaTime) {
	// Flip the player's hidden boolean and if the player is inside the hideable object
	player->hidden = !player->hidden;
	playerInside = !playerInside;
	currentEnterExitCooldown = sf::milliseconds(0);
}