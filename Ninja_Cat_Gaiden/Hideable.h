#pragma once

#include "InteractableObject.h"

class Hideable : public InteractableObject {
public:
	Hideable(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~Hideable();

	virtual void update(const sf::Time &deltaTime) override;
	virtual void action(const sf::Time &deltaTime) override;

	sf::Vector2u size;
	bool playerInside;
private:
	Player *player;
	float maxHideLength;

	sf::Time enterExitCooldown, currentEnterExitCooldown;
};