#include "Chandelier.h"
#include "Projectile.h"

#include <iostream>

Chandelier::Chandelier(sf::Vector2f &position, GamestateManager &gsm)
	: InteractableObject(position, gsm)
{
	this->type = InteractableObject::Type::Chandelier;
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->onGround = false;

	// Tweakable Variables
	this->chainSize.x = 14; // The value here should be half of the actual size you want the chain to be
	this->chainSize.y = 33; // The value here should be half of the actual size you want the chain to be
	this->fallSpeed = 1200.0f;
	this->maxSpeed = 1000.0f;
	this->collisionTune = 10;
}

Chandelier::~Chandelier() {

}

void Chandelier::update(const sf::Time &deltaTime) {
	// If the chandelier is falling and not on the ground, let it fall
	if (activated && !onGround) {
		// Change the velocity
		velocity.y += fallSpeed * deltaTime.asSeconds();
		if (velocity.y > maxSpeed) {
			velocity.y = maxSpeed;
		}

		// Keep falling until it hits a solid tile
		Tilemap *map = gsm.getCurrentState()->getTilemap();
		for (int i = 0; i < collisionTune; ++i) {
			// Check if it hits the ground, if not then move it vertically
			float yChange = velocity.y * deltaTime.asSeconds() / collisionTune;
			Tile *bottom = map->getTileByCoordinates(position.x + 63, position.y + 95 + yChange);
			if (!bottom->getSolid()) {
				position.y += yChange;
			}
			else {
				onGround = true;
			}
		}		
	}
	else {
		// Loop through the projectiles and look for collision
		std::vector<Projectile*>::iterator iterator = gsm.getCurrentState()->projectiles.begin();
		while (iterator != gsm.getCurrentState()->projectiles.end()) {
			sf::Vector2f projectilePosition = (*iterator)->position;

			if (projectilePosition.x > position.x + 64 - chainSize.x && projectilePosition.x < position.x + 64 + chainSize.x &&
				projectilePosition.y > position.y + 33 - chainSize.y && projectilePosition.y < position.y + 33 + chainSize.y) {
				activated = true;
				(*iterator)->shouldRemove = true;
			}

			iterator++;
		}
	}
}

void Chandelier::action() {
	
}