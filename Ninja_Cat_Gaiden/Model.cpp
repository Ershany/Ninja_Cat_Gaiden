#include "Model.h"
#include "Samurai.h"
#include "Chandelier.h"
#include "Hideable.h"
#include "ScrapMetalObj.h"
#include "ContainerObj.h"
#include "ChemicalObj.h"
#include "HerbObj.h"

#include <iostream>

Model::Model() {
	// Initialize the opening gamestate
	player = new Player(sf::Vector2f(7 << 5, 67 << 5), gsm);
	score = 0;
}

Model::~Model() {

}

void Model::init() {
	// Add enemies
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((20 << 5) + 20, (36 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((59 << 5) + 20, (67 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((27 << 5) + 20, (20 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[2]->maxMovement = 224;
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((3 << 5) + 20, (20 << 5) + 2), gsm, player));
	gsm.getCurrentState()->enemies[3]->maxMovement = 480;

	// Add Interactable Objects
	gsm.getCurrentState()->objects.push_back(new Chandelier(sf::Vector2f((20 << 5) - 15, (29 << 5)), gsm));
	gsm.getCurrentState()->objects.push_back(new Chandelier(sf::Vector2f((59 << 5) - 15, (50 << 5)), gsm));
	gsm.getCurrentState()->objects.push_back(new Hideable(sf::Vector2f((23 << 5) - 6, (20 << 5) - 12), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ScrapMetalObj(sf::Vector2f((46 << 5), (59 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ScrapMetalObj(sf::Vector2f((23 << 5) + 16, (17 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ContainerObj(sf::Vector2f((90 << 5), (8 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new ChemicalObj(sf::Vector2f((29 << 5), (40 << 5)), gsm, player));
	gsm.getCurrentState()->objects.push_back(new HerbObj(sf::Vector2f((15 << 5), (72 << 5)), gsm, player));
}

void Model::update(sf::Time deltaTime) {
	gsm.update(deltaTime);
}

void Model::setGSM(GamestateManager &gsm) {
	this->gsm = gsm;
}