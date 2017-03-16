#pragma once

#include "InteractableObject.h"
#include "CollectibleObject.h"

class ScrapMetalObj : public InteractableObject, public CollectibleObject {
public:
	ScrapMetalObj(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~ScrapMetalObj();

	virtual void update(const sf::Time &deltaTime) override;
	virtual void action(const sf::Time &deltaTime) override;

	sf::Vector2u size;
private:
	Player *player;
};