#include "Gamestate.h"

Gamestate::Gamestate(Tilemap *map, Player *player, Camera *camera, TextureManager *textureManager) {
	this->map = map;
	this->player = player;
	this->camera = camera;
	this->textureManager = textureManager;
}

Gamestate::~Gamestate() {

}

void Gamestate::update(const sf::Time &deltaTime) {
	map->update(deltaTime);
	player->update(deltaTime);
	camera->update(deltaTime);
	
}

void Gamestate::render() {
	camera->render();
	//window.draw(player->sprite);
}

void Gamestate::keyPressed(int keycode) {

}

void Gamestate::keyReleased(int keycode) {

}

Tilemap* Gamestate::getTilemap() {
	return map;
}