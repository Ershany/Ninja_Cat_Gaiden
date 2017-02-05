#include "Tile.h"

int Tile::width = 32;
int Tile::height = 32;

Tile::Tile() {
	this->position = sf::Vector2f(0.0f, 0.0f);
	this->solid = false;
	this->projectileSolid = false;
}

Tile::Tile(sf::Vector2f &position, bool solid, bool projectileSolid) {
	this->position = position;
	this->solid = solid;
	this->projectileSolid = projectileSolid;
}

Tile::~Tile() {

}

void Tile::update(sf::Time deltaTime) {
	this->sprite.setPosition(position.x, position.y);
}

void Tile::setPosition(sf::Vector2f position) {
	this->position = position;
}

sf::Vector2f Tile::getPosition() const {
	return position;
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