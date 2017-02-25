#include "Gamestate.h"

#include <iostream>

Gamestate::Gamestate(Tilemap *map, Camera *camera, TextureManager *textureManager) {
	this->map = map;
	this->camera = camera;
	this->textureManager = textureManager;
}

Gamestate::~Gamestate() {

}

void Gamestate::update(const sf::Time &deltaTime) {
	map->update(deltaTime);
	camera->update(deltaTime);
}

void Gamestate::render() {
	camera->render();
}

void Gamestate::keyPressed(int keycode) {
	
}

void Gamestate::keyReleased(int keycode) {

}

Tilemap* Gamestate::getTilemap() {
	return map;
}