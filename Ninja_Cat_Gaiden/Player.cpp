#include "Player.h"
#include "GamestateManager.h"
#include "Projectile.h"

#include <iostream>
#include <cmath>
#include "Defs.h"

// TODO: Make movement framerate independant
Player::Player(sf::Vector2f &pos, GamestateManager &gsm) 
	: gsm(gsm)
{
	// Non-Tweakable Variables
	this->currentLevel = 2; // Should be 1
	this->isInvincible = false;
	this->maxHealth = 10;
	this->currentHealth = maxHealth;
	this->maxStamina = 100;
	this->currentStamina = maxStamina;
	this->isDead = false;
	this->position = pos;
	this->size.x = 56;
	this->size.y = 68;
	this->jumping = false; this->canJump = false;
	this->currentFallRate = 1.0f; // Don't touch this, keeps track of the falling speed
	this->lastWallCollision.x = -100; this->lastWallCollision.y = -100;
	facingRight = true;
	this->fHeld = false;
	this->hidden = false;
	this->transitioningToNextLevel = false;
	this->score = 0;

	// Tweakable variables
	this->speed.x = 64.0f; // Horizontal Speed 
	this->speed.y = 86.0f; // Vertical Speed (Jump Speed)
	this->velocityDrag.x = 0.90f; // The rate at which velocity dissipates (Lower the faster the player stops moving)
	this->velocityDrag.y = 0.95; // The rate at which velocity dissipates (Lower the faster the player stops moving)
	this->gravitySpeed = 0.25f; // The rate at which you fall due to gravity (Higher = faster)
	this->collisionTune = 20; // Higher the value, more accurate collision is (NOTE: This may need to be turned up if the movement is fast)
	this->jumpPower = 0.25f;
	this->fallRate = 0.1f; // Higher the value, faster the player falls
	this->projectileSpeed = sf::Vector2f(1000.0f, 1000.0f);
	this->projectileFreq = sf::milliseconds(500); // The rate at which a player can throw a projectile
	this->invincibilityTime = sf::milliseconds(500); // The amount of time the player is invincible after getting hit
	this->meleeRange = 55.0f * 55.0f; // Range at which the player can melee (Note: Should be squared so square root isn't required for a distance check)
	
	// Score information
	this->meleeKillScore = 10;
	this->rangeKillScore = 5; 
	this->environmentKillScore = 25; 
	this->damageScoreDeduction = 1; 
	this->collectiblePickupScore = 5;

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

	// Check if the player is trying to shoot a projectile
	if (!isDead) {
		checkProjectileShoot(deltaTime);
		checkMelee(deltaTime);
	}
	
	// Make sure the player can jump if they are able to
	if(!isDead)
		checkJump();

	if (currentStamina < maxStamina)
		currentStamina++;

	// Update the player's velocity and position
	updateVelocity(deltaTime);
	updatePosition(deltaTime);

	// Update the sprites position (screen position)
	sprite.setPosition(position - gsm.getCurrentState()->getTilemap()->getOffset());
}

void Player::updateVelocity(const sf::Time &deltaTime) {
	// Get the horizontal input from the player
	if (!isDead) {
		float xChange = 0.0f;
		if (leftHeld) {
			xChange -= 1.0f;
			facingRight = false;
		}
		if (rightHeld) {
			xChange += 1.0f;
			facingRight = true;
		}
		// Only allow the player to jump if they are able to, and if they are not jumping on the same wall they previously jumped off of
		if (upHeld && canJump && currentStamina >= 50) {
			lastWallCollision.x = (int)position.x;
			lastWallCollision.y = (int)position.y;
			velocity.y = -jumpPower;
			jumping = true;
			currentStamina -= 50;
		}

		// Velocity Affected By Input
		velocity.x += deltaTime.asSeconds() * xChange;
	}

	// Gravity
	if (velocity.y > 0) { currentFallRate += fallRate; }
	else { currentFallRate = 1.0f; }
	velocity.y += deltaTime.asSeconds() * gravitySpeed * currentFallRate;

	// Velocity Drag
	velocity.x *= velocityDrag.x;
	velocity.y *= velocityDrag.y;
	if (abs(velocity.x) < 0.001) velocity.x = 0;
	if (abs(velocity.y) < 0.001) velocity.y = 0;
}

void Player::updatePosition(const sf::Time &deltaTime) {
	// Update the player position relative to the velocity and speed
	move(velocity.x * speed.x, velocity.y * speed.y);

	// Check if the player is taking damage
	checkTileDamage(deltaTime);

	// Check if the player's invicibility should wear off
	if (isInvincible) {
		currentInvincibilityTime += deltaTime;

		if (currentInvincibilityTime >= invincibilityTime) {
			isInvincible = false;
		}
	}
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
			else { // If the player is falling really fast they might get stuck in a tile, so set the player's position
				position.y = downwardsMiddleFootCheck->getPosition().y - size.y;
				velocity.y = 0;
			}
		}
		else if (yChange < 0) { // Upwards
			if (!upwardsLeftHeadCheck->getSolid() && !upwardsRightHeadCheck->getSolid() && !upwardsMiddleHeadCheck->getSolid()) {
				position.y += yChange;
			}
			else { // When the player jumps and hits a tile, reset the player's vertical velocity
				velocity.y = 0; 
			}
		}
		// Determine what direction needs to be checked horizontally
		if (xChange > 0) { // Right
			if (!rightwardsRightHeadCheck->getSolid() && !rightwardsRightHighMiddleCheck->getSolid() && !rightwardsRightFootCheck->getSolid() && !rightwardsRightLowMiddleCheck->getSolid()) {
				position.x += xChange;
			}
			else {
				// When the player hits the wall when going right, reset horizontal velocity
				velocity.x = 0;
			}
		}
		else if (xChange < 0) { // Left
			if (!leftwardsLeftHeadCheck->getSolid() && !leftwardsLeftHighMiddleCheck->getSolid() && !leftwardsLeftFootCheck->getSolid() && !leftwardsLeftLowMiddleCheck->getSolid()) {
				position.x += xChange;
			}
			else {
				// When the player hits the wall when going left, reset horizontal velocity
				velocity.x = 0;
			}
		}

		// Lastly, update the collision points after the movement
		updateCollisionPoints();
	}
}

void Player::checkJump() {
	// Get the tiles right below the feet of the player
	Tilemap *map = gsm.getCurrentState()->getTilemap();
	Tile *leftFootTile = map->getTileByCoordinates(collisionPoints[0] + sf::Vector2f(0.0f, 1.0f));
	Tile *rightFootTile = map->getTileByCoordinates(collisionPoints[1] + sf::Vector2f(0.0f, 1.0f));
	Tile *middleFootTile = map->getTileByCoordinates(collisionPoints[7] + sf::Vector2f(0.0f, 1.0f));

	// If one of them are solid, the player can jump
	if (leftFootTile->getSolid() || rightFootTile->getSolid() || middleFootTile->getSolid()) {
		lastWallCollision.x = (int)position.x;
		lastWallCollision.y = (int)position.y;
		canJump = true;
		jumping = false;
	}
	else {
		canJump = false;
	}

	// The player might be able to grab a wall and jump off of it
	if (facingRight) {
		Tile *rightwardsRightHighMiddleCheck = map->getTileByCoordinates(collisionPoints[4] + sf::Vector2f(1.0f, 0.0f));
		if (rightwardsRightHighMiddleCheck->getSolid() && (lastWallCollision.x != (int)position.x || lastWallCollision.y == (int)position.y)) {
			canJump = true;
		}
	}
	else {
		Tile *leftwardsLeftHighMiddleCheck = map->getTileByCoordinates(collisionPoints[5] + sf::Vector2f(-1.0f, 0.0f));
		if (leftwardsLeftHighMiddleCheck->getSolid() && (lastWallCollision.x != (int)position.x || lastWallCollision.y == (int)position.y)) {
			canJump = true;
		}
	}
}

void Player::checkTileDamage(const sf::Time &deltaTime) {
	// Get the tiles right below the feet of the player
	Tilemap *map = gsm.getCurrentState()->getTilemap();
	Tile *leftFootTile = map->getTileByCoordinates(collisionPoints[0]);
	Tile *rightFootTile = map->getTileByCoordinates(collisionPoints[1]);
	Tile *middleFootTile = map->getTileByCoordinates(collisionPoints[7]);

	// Get the tile that deals the most damage, and then take that much damage
	if (leftFootTile->getDamaging() || rightFootTile->getDamaging() || middleFootTile->getDamaging()) {
		int maxAmount = leftFootTile->getDamageAmount();
		if (rightFootTile->getDamageAmount() > maxAmount) { maxAmount = rightFootTile->getDamageAmount(); }
		if (middleFootTile->getDamageAmount() > maxAmount) { maxAmount = middleFootTile->getDamageAmount(); }

		takeDamage(maxAmount, deltaTime);
	}
}

void Player::checkProjectileShoot(const sf::Time &deltaTime) {
	// Make sure the player has the right item selected
	if (inventory.currentSelectedItem != 1 && inventory.currentSelectedItem != 2) return;

	// Add to the current time since the player last threw a projectile
	currentProjectileFreq += deltaTime;
	if (leftMouseButtonPressed && currentProjectileFreq >= projectileFreq && currentStamina >= 10) {
		// Throw a projectile and reset the time since a projectile was last thrown
		sf::Vector2f mousePosFloat(mousePos.x, mousePos.y);
		sf::Vector2f shootPosition = sprite.getPosition();
		sf::Vector2f direction = normalize(mousePosFloat - shootPosition);
	
		// Use the right item that is selected
		if (inventory.currentSelectedItem == 1) { // Shuriken
			// Make sure the player has a shuriken left
			if (inventory.numShurikens > 0) {
				shootShuriken(sf::Vector2u(16, 16), direction * projectileSpeed);
				
				// Take away one shuriken from the player
				inventory.numShurikens--;
			}		
		}
		else if (inventory.currentSelectedItem == 2) { // Smokebomb
			// Make sure the player has a smokebomb left
			if (inventory.numSmokebombs > 0) {
				shootSmokebomb(sf::Vector2u(16, 16), direction * projectileSpeed);

				// Take away one smokebomb from the player
				inventory.numSmokebombs--;
			}
		}

		currentProjectileFreq = sf::milliseconds(0);
		currentStamina -= 10;
	}
}

void Player::checkMelee(const sf::Time &deltaTime) {
	// Make sure that the katana is selected
	if (inventory.currentSelectedItem == 0 && leftMouseButtonPressed) {
		shouldMelee = true;
	}
	else {
		shouldMelee = false;
	}
}

void Player::shootShuriken(sf::Vector2u &size, sf::Vector2f &velocity, sf::Vector2f &velocityDrag) {
	gsm.getCurrentState()->projectiles.push_back(new Projectile(position, size, velocity, gsm, Projectile::Type::Shuriken, velocityDrag));
}

void Player::shootSmokebomb(sf::Vector2u &size, sf::Vector2f &velocity, sf::Vector2f &velocityDrag) {
	gsm.getCurrentState()->projectiles.push_back(new Projectile(position, size, velocity, gsm, Projectile::Type::Smokebomb, velocityDrag));
}

void Player::takeDamage(int amount, const sf::Time &deltaTime) {
	if(!isInvincible) {
		score -= minimumNum(damageScoreDeduction * amount, currentHealth);
		currentHealth -= amount;
		isInvincible = true;
		currentInvincibilityTime = sf::milliseconds(0);

		if (currentHealth <= 0) {
			currentHealth = 0;
			isDead = true;
		}
	}
}

sf::Vector2u Player::getSize() {
	return size;
}

sf::Vector2f Player::getVelocity() {
	return velocity;
}

int Player::getCurrHealth() {
	return currentHealth;
}

int Player::getMaxHealth() {
	return maxHealth;
}

int Player::getCurrStamina() {
	return currentStamina;
}

int Player::getMaxStamina() {
	return maxStamina;
}