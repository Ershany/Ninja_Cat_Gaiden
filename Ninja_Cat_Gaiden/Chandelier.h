#pragma once

#include "InteractableObject.h"

class Chandelier : public InteractableObject {
public:
	Chandelier(sf::Vector2f &position, GamestateManager &gsm, Player *player);
	~Chandelier();

	virtual void update(const sf::Time &deltaTime) override;
	virtual void action(const sf::Time &deltaTime) override;
private:
	sf::Vector2i chainSize;
	float intersectionLength;
	
	float fallSpeed;
	sf::Vector2f velocity;
	float maxSpeed;
	int collisionTune;
	bool onGround;

	Player *player;
};