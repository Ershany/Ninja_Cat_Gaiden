#include "Samurai.h"

Samurai::Samurai(sf::Vector2f &position, GamestateManager &gsm) 
	: Enemy(position, gsm)
{
	this->type = Type::Samurai;
}

Samurai::~Samurai() {

}

void Samurai::update(const sf::Time &deltaTime) {

}