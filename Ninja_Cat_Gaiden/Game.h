#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>

#include "InputManager.h"
#include "Tilemap.h"
#include "TextureManager.h"
#include "Player.h"
#include "Camera.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

class Game {
public:
	Game();
	~Game();

	void launch();
private:
	Model *model;
	View *view;
	Controller *controller;
	
	sf::Clock clock;
};

#endif