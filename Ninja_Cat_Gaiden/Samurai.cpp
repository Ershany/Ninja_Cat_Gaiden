#include "Samurai.h"

#include "Defs.h"

#include <iostream>

Samurai::Samurai(sf::Vector2f &position, GamestateManager &gsm, Player *player) 
	: Enemy(position, gsm, player)
{
	this->type = Type::Samurai;
	this->moving = true;
	this->currentWaitTime = sf::milliseconds(0);
	
	// Tweakable Variables
	this->size.x = 67;
	this->size.y = 62;
	this->lengthPerSightCheck = 10;
	this->speed.x = 250.0f;
	this->speed.y = 0.0f;
	this->waitTime = sf::milliseconds(3000);
	this->sightRange = 650.0f;
}

Samurai::~Samurai() {

}

void Samurai::update(const sf::Time &deltaTime) {
	// Get the tilemap
	Tilemap *map = gsm.getCurrentState()->getTilemap();

	// Update the samurai's movement
	if (moving) {
		move(deltaTime);
	}
	else {
		// Update the current amount of time since the samurai last moved
		currentWaitTime += deltaTime;
		// If they waited long enough, then change their movement to the other direction
		if (currentWaitTime >= waitTime) {
			moving = true;
			facingRight = !facingRight;
			currentWaitTime = sf::milliseconds(0);
		}
	}

	// Check if the player is within range
	sf::Vector2f difference = player->position - position;
	float differenceLength = length(difference);
	if (differenceLength <= sightRange && ((facingRight && difference.x >= 0) || (!facingRight && difference.x <= 0))) {
		// Get the current raycast position and how much to update it every iteration of the for loop
		sf::Vector2f currentSightPos = position + sf::Vector2f(size.x * 0.5f, size.y * 0.2f);
		int iterationAmount = differenceLength / lengthPerSightCheck;
		sf::Vector2f updateAmount = sf::Vector2f(difference.x / iterationAmount, difference.y / iterationAmount);
		// Check if the player can be seen from this point
		for (int i = 0; i < iterationAmount; i++) {
			if (map->getTileByCoordinates(currentSightPos)->getSolid()) {
				alertOfPlayer = false;
				break;
			}
			else {
				alertOfPlayer = true;
			}
			currentSightPos += updateAmount;
		}
	}
	else {
		alertOfPlayer = false;
	}
}

void Samurai::move(const sf::Time &deltaTime) {
	// Get the tilemap
	Tilemap *map = gsm.getCurrentState()->getTilemap();

	Tile* footCheckTile = NULL;
	if (facingRight) {
		footCheckTile = map->getTileByCoordinates(position + sf::Vector2f(size.x + 1, size.y + 1));
		// Move the samurai
		position.x += speed.x * deltaTime.asSeconds();
	}
	else {
		footCheckTile = map->getTileByCoordinates(position + sf::Vector2f(-1.0f, size.y + 1));
		// Move the samurai
		position.x -= speed.x * deltaTime.asSeconds();
	}

	if (!footCheckTile->getSolid()) {
		moving = false;
	}
}