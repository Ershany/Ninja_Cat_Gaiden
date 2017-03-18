#include "Gamestate.h"

#include "Projectile.h"
#include "Enemy.h"
#include "InteractableObject.h"

#include <iostream>

Gamestate::Gamestate(Tilemap *map, Camera *camera, TextureManager *textureManager) {
	this->map = map;
	this->camera = camera;
	this->textureManager = textureManager;
	this->gameover = false;
	this->inMenu = false;
	this->popOffState = false;
	this->shouldRestart = false;
}

Gamestate::~Gamestate() {
	std::vector<InteractableObject*>::iterator objectIterator = objects.begin();
	while (objectIterator != objects.end()) {
		delete (*objectIterator);
		objectIterator++;
	}

	std::vector<Projectile*>::iterator iterator = projectiles.begin();
	while (iterator != projectiles.end()) {
		delete (*iterator);
		iterator++;
	}

	std::vector<Enemy*>::iterator enemyIterator = enemies.begin();
	while (enemyIterator != enemies.end()) {
		delete (*enemyIterator);
		enemyIterator++;
	}

	delete camera;
}

void Gamestate::update(const sf::Time &deltaTime) {
	if (!gameover) {
		if(map != NULL)
			map->update(deltaTime);
		updateProjectiles(deltaTime);
		updateEnemies(deltaTime);
		updateObjects(deltaTime);
		if(camera != NULL)
			camera->update(deltaTime);
	}
}

void Gamestate::render() {
	if(camera != NULL)
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

void Gamestate::updateObjects(const sf::Time &deltaTime) {
	std::vector<InteractableObject*>::iterator iterator = objects.begin();
	while (iterator != objects.end()) {
		// Check if the object should be removed
		if ((*iterator)->shouldRemove) {
			delete (*iterator);
			iterator = objects.erase(iterator);
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