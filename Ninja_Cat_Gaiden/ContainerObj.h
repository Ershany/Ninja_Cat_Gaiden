#pragma once

#include "InteractableObject.h"
#include "CollectibleObject.h"

class ContainerObj : public InteractableObject, public CollectibleObject {
public:
	ContainerObj(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~ContainerObj();

	virtual void update(const sf::Time &deltaTime) override;
	virtual void action(const sf::Time &deltaTime) override;

	sf::Vector2u size;
private:
	Player *player;
};