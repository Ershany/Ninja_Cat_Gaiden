#pragma once

#include "Model.h"
#include "TextureManager.h"
#include "GamestateManager.h"
#include "HUD.h"

class View {
public:
	View(Model *model, GamestateManager &gsm);
	~View();
	
	void render();
	void checkForTransition();
	
	Model *model;

	sf::RenderWindow window;
	TextureManager textureManager;
	GamestateManager &gsm;
	HUD *hud;
};