#include "Model.h"

Model::Model() {
	// Initialize the opening gamestate
	player = new Player(sf::Vector2f(48.0f, 48.0f), gsm);
}

Model::~Model() {

}

void Model::update(sf::Time deltaTime) {
	gsm.update(deltaTime);
}

void Model::setGSM(GamestateManager &gsm) {
	this->gsm = gsm;
}