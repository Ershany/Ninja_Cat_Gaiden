#pragma once

#include "Model.h"
#include "TextureManager.h"
#include "GamestateManager.h"

class View {
public:
	View(Model *model, GamestateManager &gsm);
	~View();
	
	void render();


	Model *model;
	
	sf::RenderWindow window;
	TextureManager textureManager;
	GamestateManager &gsm;
};