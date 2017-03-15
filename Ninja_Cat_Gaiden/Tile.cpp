#include "Tile.h"

int Tile::width = 32;
int Tile::height = 32;

Tile::Tile() {
	this->position = sf::Vector2f(0.0f, 0.0f);
	this->solid = false;
	this->seeAble = true;
	this->projectileSolid = false;
	this->damaging = false;
	this->damageAmount = 0;
}

Tile::Tile(sf::Vector2f &position, bool solid, bool projectileSolid) {
	this->position = position;
	this->solid = solid;
	this->projectileSolid = projectileSolid;
}

Tile::~Tile() {

}

void Tile::update(const sf::Time &deltaTime) {
	this->sprite.setPosition(position.x, position.y);
}

void Tile::setPosition(sf::Vector2f &position) {
	this->position = position;
}

sf::Vector2f Tile::getPosition() const {
	return position;
}

void Tile::setSolid(bool choice) {
	this->solid = choice;
}

void Tile::setSeeAble(bool choice) {
	this->seeAble = choice;
}

void Tile::setProjectileSolid(bool choice) {
	this->projectileSolid = choice;
}

void Tile::setTransparent(bool choice) {
	this->transparent = choice;
}

void Tile::setDamaging(bool choice) {
	damaging = choice;
}

void Tile::setDamageAmount(int amount) {
	damageAmount = amount;
}

bool Tile::getSolid() const {
	return solid;
}

bool Tile::getSeeAble() const {
	return seeAble;
}

bool Tile::getProjecitleSolid() const {
	return projectileSolid;
}

bool Tile::getTransparent() const {
	return transparent;
}

bool Tile::getDamaging() const {
	return damaging;
}

int Tile::getDamageAmount() const {
	return damageAmount;
}