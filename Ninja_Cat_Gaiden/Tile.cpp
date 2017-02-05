#include "Tile.h"

int Tile::width = 32;
int Tile::height = 32;

Tile::Tile(int x, int y, bool solid, bool projectileSolid) {
	this->x = x;
	this->y = y;
	this->solid = solid;
	this->projectileSolid = projectileSolid;
}

Tile::~Tile() {

}

void Tile::update(sf::Time deltaTime) {

}

void Tile::setSolid(bool choice) {
	this->solid = choice;
}

void Tile::setProjectileSolid(bool choice) {
	this->projectileSolid = choice;
}

bool Tile::getSolid() const {
	return solid;
}

bool Tile::getProjecitleSolid() const {
	return projectileSolid;
}