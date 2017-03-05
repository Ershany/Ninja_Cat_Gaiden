#pragma once

#include "InteractableObject.h"

class Chandelier : public InteractableObject {
public:
	Chandelier(sf::Vector2f &position, GamestateManager &gsm);
	~Chandelier();

	void update(const sf::Time &deltaTime) override;
	void action() override;
private:
	sf::Vector2i chainSize;
	float intersectionLength;
	
	float fallSpeed;
	sf::Vector2f velocity;
	float maxSpeed;
	int collisionTune;
	bool onGround;
};