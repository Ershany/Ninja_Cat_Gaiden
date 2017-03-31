#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"
#include "Inventory.h"

// Forward declaration to get around the circular reference
class GamestateManager;

class Player : public Updateable, public Renderable {
public:
	Player(sf::Vector2f &position, GamestateManager &gsm);
	~Player();

	void update(const sf::Time &deltaTime) override;

	//Getters
	sf::Vector2f getVelocity();
	sf::Vector2u getSize();
	int getCurrHealth();
	int getMaxHealth();
	int getCurrStamina();
	int getMaxStamina();
	void updateCollisionPoints();

	bool upHeld, downHeld, leftHeld, rightHeld, fHeld;
	bool shouldMelee;
	bool leftMouseButtonPressed;
	bool isDead;
	bool gameFinished;
	bool isInvincible;
	bool hidden;
	sf::Vector2i mousePos;
	bool facingRight;
	sf::Vector2f collisionPoints[10]; // Used for collision detection
	sf::Vector2u size;
	sf::Sprite deadSprite;
	Inventory inventory;
	bool transitioningToNextLevel;
	int currentLevel;
	float meleeRange;

	int score;
	int meleeKillScore, rangeKillScore, environmentKillScore, damageScoreDeduction, collectiblePickupScore;

	bool camoPotion;
	sf::Time currentCamoPotionTime, camoPotionTime;

	sf::Time currentHealthPotionTime, healthPotionTime;

	int maxHealth, currentHealth;
private:
	void updateVelocity(const sf::Time &deltaTime);
	void updatePosition(const sf::Time &deltaTime);
	void move(float x, float y);
	void checkProjectileShoot(const sf::Time &deltaTime);
	void checkMelee(const sf::Time &deltaTime);
	void checkTileDamage(const sf::Time &deltaTime);
	void takeDamage(int amount, const sf::Time &deltaTime);
	/* Determines if the player can jump, and sets the boolean "canJump" accordingly */
	void checkJump();
	/* Default velocityDrag provided : Vector2f(1.0f, 1.0f) */
	void shootShuriken(sf::Vector2u &size, sf::Vector2f &velocity, sf::Vector2f &velocityDrag = sf::Vector2f(1.0f, 1.0f));
	void shootSmokebomb(sf::Vector2u &size, sf::Vector2f &velocity, sf::Vector2f &velocityDrag = sf::Vector2f(1.0f, 1.0f));

	int maxStamina, currentStamina;

	sf::Vector2f speed;
	sf::Vector2f velocity;

	int collisionTune;
	sf::Vector2f velocityDrag;
	float gravitySpeed, fallRate, currentFallRate;
	bool jumping, canJump;
	float jumpPower;
	sf::Vector2i lastWallCollision;

	sf::Time projectileFreq, currentProjectileFreq;
	sf::Vector2f projectileSpeed;

	sf::Time invincibilityTime, currentInvincibilityTime;
	int healAmount;

	sf::Time scoreDecay, currentScoreDecay;
	int scoreDecayAmount;

	GamestateManager &gsm;
};

#endif