#pragma once

#include "Enemy.h"

class Samurai : public Enemy {
public:
	Samurai(sf::Vector2f &position, GamestateManager &gsm);
	~Samurai();

	void update(const sf::Time &deltaTime) override;
};