#pragma once

#include "Model.h"
#include "TextureManager.h"

class HUD {
public:
	HUD(Model*, sf::RenderWindow*, TextureManager*);
	~HUD();

	Model* model;
	sf::RenderWindow* window;
	TextureManager* textureManager;

	sf::Font centuryGothic;

	sf::RectangleShape health;
	sf::RectangleShape stamina;
	sf::Text score;
	sf::Text hiddenInfo;
	sf::Text equippedItemQuantity;
	sf::Sprite hudMain;
	sf::Sprite item;
	sf::Sprite gameover;

	void draw();
	void setStats();
};