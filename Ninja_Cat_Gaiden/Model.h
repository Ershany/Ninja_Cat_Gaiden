#pragma once

#include <SFML\Graphics.hpp>

#include "GamestateManager.h"

class Model {
public:
	Model();
	~Model();

	void update(sf::Time deltaTime);
	
	void setGSM(GamestateManager &gsm);

	
	GamestateManager gsm;
	Player *player;
};