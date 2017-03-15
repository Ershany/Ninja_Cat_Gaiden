#include "Samurai.h"

#include "Defs.h"

#include <iostream>

Samurai::Samurai(sf::Vector2f &position, GamestateManager &gsm, Player *player) 
	: Enemy(position, gsm, player)
{
	this->type = Type::Samurai;
	
	// Tweakable Variables
	this->size.x = 67;
	this->size.y = 62;
	this->lengthPerSightCheck = 10;
}

Samurai::~Samurai() {

}

void Samurai::update(const sf::Time &deltaTime) {
	// Get the tilemap
	Tilemap *map = gsm.getCurrentState()->getTilemap();

	// Check if the player is within range
	sf::Vector2f difference = player->position - position;
	float differenceLength = length(difference);
	if (differenceLength <= 400 && ((facingRight && difference.x >= 0) || (!facingRight && difference.x <= 0))) {
		// Get the current raycast position and howmuch to update it every iteration of the for loop
		sf::Vector2f currentSightPos = position + sf::Vector2f(size.x * 0.5f, size.y * 0.5f);
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