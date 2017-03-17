#pragma once

#include "InteractableObject.h"
#include "CollectibleObject.h"

class ExitPortal : public InteractableObject, public CollectibleObject {
public:
	ExitPortal(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~ExitPortal();

	virtual void update(const sf::Time &deltaTime) override;
	virtual void action(const sf::Time &deltaTime) override;

	sf::Vector2u size;
};