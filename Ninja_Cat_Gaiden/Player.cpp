#include "Player.h"
#include "GamestateManager.h"

#include <iostream>
#include <cmath>

Player::Player(sf::Vector2f &pos, GamestateManager &gsm) 
	: gsm(gsm)
{
	this->position = pos;
	this->size.x = 56;
	this->size.y = 68;

	// Tweakable variables
	this->speed.x = 84.0f; // Horizontal Speed
	this->speed.y = 116.0f; // Vertical Speed (Jump Speed)
	this->velocityDrag = 0.9f; // The rate at which velocity dissipates (Lower the faster the player stops moving)
	this->gravitySpeed = 0.25f; // The rate at which you fall due to gravity (Higher = faster)
	this->collisionTune = 15; // Higher the value, more accurate collision is

	// Initialize required variables
	downHeld = false; upHeld = false; rightHeld = false; leftHeld = false;
	updateCollisionPoints();
}

Player::~Player() {

}

void Player::update(const sf::Time &deltaTime) {
	// Make sure a gamestate is currently being played, log it if there is no gamestate on the stack
	if (gsm.getCurrentState() == NULL) {
		std::cout << "Player Update Cancelled: No Gamestate On The Stack" << std::endl;
		return;
	}

	updateVelocity(deltaTime);
	updatePosition(deltaTime);

	// Update the sprites position (screen position)
	sprite.setPosition(position - gsm.getCurrentState()->getTilemap()->getOffset());
}

void Player::updateVelocity(const sf::Time &deltaTime) {
	float xChange = 0.0f;
	float yChange = 0.0f;
	if (upHeld) yChange -= 1.0f;
	if (downHeld) yChange += 1.0f;
	if (leftHeld) xChange -= 1.0f;
	if (rightHeld) xChange += 1.0f;

	// Velocity Affected By Input
	velocity.x += deltaTime.asSeconds() * xChange;
	velocity.y += deltaTime.asSeconds() * yChange;

	// Gravity
	velocity.y += deltaTime.asSeconds() * gravitySpeed;

	// Velocity Drag
	velocity.x *= velocityDrag;
	velocity.y *= velocityDrag;
	if (abs(velocity.x) < 0.001) velocity.x = 0;
	if (abs(velocity.y) < 0.001) velocity.y = 0;
}

void Player::updatePosition(const sf::Time &deltaTime) {
	// Update the player position relative to the velocity and speed
	//position.x += velocity.x * speed;
	//position.y += velocity.y * speed;
	move(velocity.x * speed.x, velocity.y * speed.y);
}

void Player::updateCollisionPoints() {
	collisionPoints[0] = sf::Vector2f(position.x, position.y + size.y - 1); // Bottom left
	collisionPoints[1] = sf::Vector2f(position.x + size.x - 1, position.y + size.y - 1); // Bottom Right
	collisionPoints[2] = sf::Vector2f(position.x, position.y); // Top Left
	collisionPoints[3] = sf::Vector2f(position.x + size.x - 1, position.y); // Top Right
	collisionPoints[4] = sf::Vector2f(position.x + size.x - 1, position.y + (size.y / 4) + 1); // High Middle Right
	collisionPoints[5] = sf::Vector2f(position.x, position.y + (size.y / 4) + 1); // High Middle Left
	collisionPoints[6] = sf::Vector2f(position.x + (size.x / 2), position.y); // Top Middle
	collisionPoints[7] = sf::Vector2f(position.x + (size.x / 2), position.y + size.y - 1); // Bottom Middle

	collisionPoints[8] = sf::Vector2f(position.x + size.x - 1, position.y + (size.y * 0.75) - 1); // High Middle Right
	collisionPoints[9] = sf::Vector2f(position.x, position.y + (size.y * 0.75) - 1); // High Middle Left
}

void Player::move(float x, float y) {
	// Check all edges of the player to see what tile they are on
	Tilemap *map = gsm.getCurrentState()->getTilemap();

	// Calculate how much to move the player
	float xChange = x / collisionTune;
	float yChange = y / collisionTune;

	for (int i = 0; i < collisionTune; ++i) {
		// Get the which tile all of the collision points are on
		Tile *downwardsLeftFootCheck = map->getTileByCoordinates(collisionPoints[0] + sf::Vector2f(0.0f, 1.0f));
		Tile *downwardsRightFootCheck = map->getTileByCoordinates(collisionPoints[1] + sf::Vector2f(0.0f, 1.0f));
		Tile *downwardsMiddleFootCheck = map->getTileByCoordinates(collisionPoints[7] + sf::Vector2f(0.0f, 1.0f));
		Tile *upwardsLeftHeadCheck = map->getTileByCoordinates(collisionPoints[2] + sf::Vector2f(0.0f, -1.0f));
		Tile *upwardsRightHeadCheck = map->getTileByCoordinates(collisionPoints[3] + sf::Vector2f(0.0f, -1.0f));
		Tile *upwardsMiddleHeadCheck = map->getTileByCoordinates(collisionPoints[6] + sf::Vector2f(0.0f, -1.0f));
		Tile *leftwardsLeftHeadCheck = map->getTileByCoordinates(collisionPoints[2] + sf::Vector2f(-1.0f, 0.0f));
		Tile *leftwardsLeftHighMiddleCheck = map->getTileByCoordinates(collisionPoints[5] + sf::Vector2f(-1.0f, 0.0f));
		Tile *leftwardsLeftLowMiddleCheck = map->getTileByCoordinates(collisionPoints[9] + sf::Vector2f(-1.0f, 0.0f));
		Tile *leftwardsLeftFootCheck = map->getTileByCoordinates(collisionPoints[0] + sf::Vector2f(-1.0f, 0.0f));
		Tile *rightwardsRightHeadCheck = map->getTileByCoordinates(collisionPoints[3] + sf::Vector2f(1.0f, 0.0f));
		Tile *rightwardsRightHighMiddleCheck = map->getTileByCoordinates(collisionPoints[4] + sf::Vector2f(1.0f, 0.0f));
		Tile *rightwardsRightLowMiddleCheck = map->getTileByCoordinates(collisionPoints[8] + sf::Vector2f(1.0f, 0.0f));
		Tile *rightwardsRightFootCheck = map->getTileByCoordinates(collisionPoints[1] + sf::Vector2f(1.0f, 0.0f));

		// Check if the player is out of the map, to avoid a null pointer exception
		if (downwardsLeftFootCheck == NULL || downwardsRightFootCheck == NULL || upwardsLeftHeadCheck == NULL || upwardsRightHeadCheck == NULL ||
			leftwardsLeftFootCheck == NULL || leftwardsLeftHeadCheck == NULL || rightwardsRightFootCheck == NULL || rightwardsRightHeadCheck == NULL) {
			// Log it
			std::cout << "Player Out Of The Map: Can't Move The Player" << std::endl;
			return;
		}
		
		// Determine what direction needs to be checked vertically
		if (yChange > 0) { // Downwards
			if (!downwardsLeftFootCheck->getSolid() && !downwardsRightFootCheck->getSolid() && !downwardsMiddleFootCheck->getSolid()) {
				position.y += yChange;
			}
		}
		else if (yChange < 0) { // Upwards
			if (!upwardsLeftHeadCheck->getSolid() && !upwardsRightHeadCheck->getSolid() && !upwardsMiddleHeadCheck->getSolid()) {
				position.y += yChange;
			}
		}
		// Determine what direction needs to be checked horizontally
		if (xChange > 0) { // Right
			if (!rightwardsRightHeadCheck->getSolid() && !rightwardsRightHighMiddleCheck->getSolid() && !rightwardsRightFootCheck->getSolid() && !rightwardsRightLowMiddleCheck->getSolid()) {
				position.x += xChange;
			}
		}
		else if (xChange < 0) { // Left
			if (!leftwardsLeftHeadCheck->getSolid() && !leftwardsLeftHighMiddleCheck->getSolid() && !leftwardsLeftFootCheck->getSolid() && !leftwardsLeftLowMiddleCheck->getSolid()) {
				position.x += xChange;
			}
		}

		//position.x += xChange;
		//position.y += yChange;
		

		// Lastly, update the collision points after the movement
		updateCollisionPoints();
	}
}

sf::Vector2u Player::getSize() {
	return size;
}