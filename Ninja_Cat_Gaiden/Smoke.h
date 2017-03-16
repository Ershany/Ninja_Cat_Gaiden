#pragma once

#include "InteractableObject.h"

class Smoke : public InteractableObject {
public:
	Smoke(sf::Vector2f &position, GamestateManager &gsm);
	~Smoke();

	virtual void update(const sf::Time &deltaTime) override;
	virtual void action() override;
private:
	sf::Time current, duration;

	sf::Vector2u size;
	bool **tileSeeAble;
};