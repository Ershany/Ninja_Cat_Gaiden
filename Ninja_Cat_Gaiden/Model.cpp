#include "Model.h"
#include "Samurai.h"
#include "Chandelier.h"

Model::Model() {
	// Initialize the opening gamestate
	player = new Player(sf::Vector2f(7 << 5, 67 << 5), gsm);
	score = 0;
}

Model::~Model() {

}

void Model::init() {
	// Add enemies
	gsm.getCurrentState()->enemies.push_back(new Samurai(sf::Vector2f((20 << 5) + 20, (36 << 5) + 2), gsm));

	// Add Interactable Objects
	gsm.getCurrentState()->objects.push_back(new Chandelier(sf::Vector2f((20 << 5) - 15, (29 << 5)), gsm));
}

void Model::update(sf::Time deltaTime) {
	gsm.update(deltaTime);
}

void Model::setGSM(GamestateManager &gsm) {
	this->gsm = gsm;
}