#include "Projectile.h"
#include "Smoke.h"

#include <iostream>

Projectile::Projectile(sf::Vector2f &position, sf::Vector2u &size, sf::Vector2f &velocity, GamestateManager &gsm, Type type, sf::Vector2f &velocityDrag)
	: gsm(gsm)
{
	this->position = position;
	this->size = size;
	this->velocity = velocity;
	this->velocityDrag = velocityDrag;
	this->shouldRemove = false;
	this->type = type;

	// Tweakable Variables
	this->collisionTune = 5;

	updateCollisionPoints();
}

Projectile::~Projectile() {

}

void Projectile::update(const sf::Time &deltaTime) {
	// Update the projectile position
	move(velocity.x * deltaTime.asSeconds(), velocity.y * deltaTime.asSeconds());

	// Change the projectiles velocity (TODO: Change this to be framerate independant)
	this->velocity.x *= velocityDrag.x;
	this->velocity.y *= velocityDrag.y;
}

void Projectile::updateCollisionPoints() {
	collisionPoints[0] = sf::Vector2f(position.x, position.y + size.y - 1); // Bottom left
	collisionPoints[1] = sf::Vector2f(position.x + size.x - 1, position.y + size.y - 1); // Bottom Right
	collisionPoints[2] = sf::Vector2f(position.x, position.y); // Top Left
	collisionPoints[3] = sf::Vector2f(position.x + size.x - 1, position.y); // Top Right
}

void Projectile::move(float x, float y) {
	// Check all edges of the player to see what tile they are on
	Tilemap *map = gsm.getCurrentState()->getTilemap();

	// Calculate how much to move the player
	float xChange = x / collisionTune;
	float yChange = y / collisionTune;

	for (int i = 0; i < collisionTune; ++i) {
		Tile *bottomLeftCheck = map->getTileByCoordinates(collisionPoints[0] + sf::Vector2f(xChange, yChange));
		Tile *bottomRightCheck = map->getTileByCoordinates(collisionPoints[1] + sf::Vector2f(xChange, yChange));
		Tile *topLeftCheck = map->getTileByCoordinates(collisionPoints[2] + sf::Vector2f(xChange, yChange));
		Tile *topRightCheck = map->getTileByCoordinates(collisionPoints[3] + sf::Vector2f(xChange, yChange));

		// Check if the projectile is out of the map, to avoid a null pointer exception
		if (bottomLeftCheck == NULL || bottomRightCheck == NULL || topLeftCheck == NULL || topRightCheck == NULL) {
			// Log it
			std::cout << "Projectile Out Of The Map: Can't Move The Projectile" << std::endl;
			shouldRemove = true;
			return;
		}

		// Check if there is any intersection
		if (bottomLeftCheck->getSolid() || bottomRightCheck->getSolid() || topLeftCheck->getSolid() || topRightCheck->getSolid()) {
			shouldRemove = true;
			// Check if we should spawn smoke
			if (type == Projectile::Type::Smokebomb) {
				gsm.getCurrentState()->objects.push_back(new Smoke(position - sf::Vector2f(128.0f, 128.0f), gsm));
			}
		}
		else {
			this->position.x += xChange;
			this->position.y += yChange;
		}
	}

	updateCollisionPoints();
}