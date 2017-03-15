#pragma once

#include "Enemy.h"

class Samurai : public Enemy {
public:
	Samurai(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~Samurai();

	void update(const sf::Time &deltaTime) override;
private:
	int lengthPerSightCheck; // Smaller the value, the more accurate
};