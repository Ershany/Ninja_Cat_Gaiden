#include "Enemy.h"

Enemy::Enemy(sf::Vector2f &position, GamestateManager &gsm)
	: gsm(gsm)
{
	this->position = position;
	this->shouldRemove = false;
}

Enemy::~Enemy() {

}

void Enemy::update(const sf::Time &deltaTime) {

}