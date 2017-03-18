#pragma once

#include <SFML\Graphics.hpp>

#include "GamestateManager.h"
#include "Projectile.h"

class Model {
public:
	Model();
	~Model();

	// Must be called after the model, view, and controller are setup
	void initLevel1();
	void initLevel2();
	void initLevel3();
	void update(sf::Time deltaTime);
	
	void setGSM(GamestateManager &gsm);

	
	GamestateManager gsm;
	Player *player;
	
	//int score;
};