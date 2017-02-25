#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"

// Forward declaration to get around the circular reference
class GamestateManager;

class Player : public Updateable, public Renderable {
public:
	Player(sf::Vector2f &position, GamestateManager &gsm);
	~Player();

	void update(const sf::Time &deltaTime);

	sf::Vector2u getSize();

	bool upHeld, downHeld, leftHeld, rightHeld;
	sf::Vector2f collisionPoints[10]; // Used for collision detection
private:
	void updateVelocity(const sf::Time &deltaTime);
	void updatePosition(const sf::Time &deltaTime);
	void updateCollisionPoints();
	void move(float x, float y);

	sf::Vector2f speed;
	float velocityDrag;
	float gravitySpeed;
	sf::Vector2f velocity;
	sf::Vector2u size;
	int collisionTune;

	GamestateManager &gsm;
};

#endif