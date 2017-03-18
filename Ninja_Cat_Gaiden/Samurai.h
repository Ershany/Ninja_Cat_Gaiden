#pragma once

#include "Enemy.h"

class Samurai : public Enemy {
public:
	Samurai(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~Samurai();

	void update(const sf::Time &deltaTime) override;
	bool moving;
private:
	int lengthPerSightCheck; // Smaller the value, the more accurate

	sf::Time waitTime, currentWaitTime;

	void move(const sf::Time &deltaTime);
	void checkSight();
};