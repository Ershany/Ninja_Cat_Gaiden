#pragma once

#include "InteractableObject.h"

class Hideable : public InteractableObject {
public:
	Hideable(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~Hideable();

	virtual void update(const sf::Time &deltaTime) override;
	virtual void action() override;

	sf::Vector2u size;
	bool playerInside;
private:
	Player *player;
	float maxHideLength;
};