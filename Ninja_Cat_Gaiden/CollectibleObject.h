#pragma once

#include "Player.h"

class CollectibleObject {
public:
	CollectibleObject(sf::Vector2f objectPosition, sf::Vector2u size, Player *player);

protected:
	bool isPlayerTakingObject();
	Player *player;
	sf::Vector2u size;
	float maxGrabLength;
private:
	sf::Vector2f objectPosition;
};