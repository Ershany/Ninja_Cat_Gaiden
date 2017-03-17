#pragma once

#include "InteractableObject.h"
#include "CollectibleObject.h"

class HerbObj : public InteractableObject, public CollectibleObject {
public:
	HerbObj(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~HerbObj();

	virtual void update(const sf::Time &deltaTime) override;
	virtual void action(const sf::Time &deltaTime) override;

	sf::Vector2u size;
};