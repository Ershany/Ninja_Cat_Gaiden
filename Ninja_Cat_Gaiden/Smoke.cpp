#include "Smoke.h"

#include <iostream>

Smoke::Smoke(sf::Vector2f &position, GamestateManager &gsm)
	: InteractableObject(position, gsm)
{
	this->type = InteractableObject::Type::Smoke;
	this->current = sf::milliseconds(0);
	this->size.x = 224; this->size.y = 224;

	// Tweakable Variables
	this->duration = sf::milliseconds(5000);

	// Make all of the blocks in the smoke cloud not seeable
	tileSeeAble = new bool*[size.y >> 5];
	Tilemap *map = gsm.getCurrentState()->getTilemap();
	for (int row = 0; row < (size.y >> 5); ++row) {
		tileSeeAble[row] = new bool[size.x >> 5];
		for (int col = 0; col < (size.x >> 5); ++col) {
			Tile *current = map->getTileByCoordinates(position + sf::Vector2f(col << 5, row << 5));
			if (current != NULL) {
				// Set its original value depending if the tile was solid or not
				tileSeeAble[row][col] = current->getSolid();
				// Then make it so it can't be seeable
				current->setSeeAble(false);
			}
		}
	}

	// Testing print out
	/*for (int row = 0; row < (size.y >> 5); ++row) {
		for (int col = 0; col < (size.x >> 5); ++col) {
			std::cout << tileSeeAble[row][col] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;*/
}

Smoke::~Smoke() {
	
}

void Smoke::update(const sf::Time &deltaTime) {
	current += deltaTime;

	if (current >= duration) {
		shouldRemove = true;

		// Set the tiles seeable property back to what it was originally
		Tilemap *map = gsm.getCurrentState()->getTilemap();
		for (int row = 0; row < (size.y >> 5); ++row) {
			for (int col = 0; col < (size.x >> 5); ++col) {
				Tile *current = map->getTileByCoordinates(position + sf::Vector2f(col << 5, row << 5));
				if (current != NULL) {
					// Set the tile back to its original unaltered value
					current->setSeeAble(!tileSeeAble[row][col]);
				}
			}
		}
	}
}

void Smoke::action(const sf::Time &deltaTime) {

}