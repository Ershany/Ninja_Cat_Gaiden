#pragma once

#include "InteractableObject.h"
#include "CollectibleObject.h"

class ChemicalObj : public InteractableObject, public CollectibleObject {
public:
	ChemicalObj(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~ChemicalObj();

	virtual void update(const sf::Time &deltaTime) override;
	virtual void action(const sf::Time &deltaTime) override;

	sf::Vector2u size;
};