#include "Gamestate.h"

#include "Projectile.h"
#include "Enemy.h"

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
	updateProjectiles(deltaTime);
	updateEnemies(deltaTime);
	camera->update(deltaTime);
}

void Gamestate::render() {
	camera->render();
}

void Gamestate::keyPressed(int keycode) {
	
}

void Gamestate::keyReleased(int keycode) {

}

void Gamestate::updateProjectiles(const sf::Time &deltaTime) {
	std::vector<Projectile*>::iterator iterator = projectiles.begin();
	while (iterator != projectiles.end()) {
		// Check if the projectile should be removed
		if ((*iterator)->shouldRemove) {
			delete (*iterator);
			iterator = projectiles.erase(iterator);
		}
		else { // else update it
			(*iterator)->update(deltaTime);
			iterator++;
		}
	}
}

void Gamestate::updateEnemies(const sf::Time &deltaTime) {
	std::vector<Enemy*>::iterator iterator = enemies.begin();
	while (iterator != enemies.end()) {
		// Check if the enemy should be removed
		if ((*iterator)->shouldRemove) {
			delete (*iterator);
			iterator = enemies.erase(iterator);
		}
		else { // else update it
			(*iterator)->update(deltaTime);
			iterator++;
		}
	}
}

Tilemap* Gamestate::getTilemap() {
	return map;
}