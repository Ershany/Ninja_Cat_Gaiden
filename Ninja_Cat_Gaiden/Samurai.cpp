#include "Samurai.h"

Samurai::Samurai(sf::Vector2f &position, GamestateManager &gsm) 
	: Enemy(position, gsm)
{
	this->type = Type::Samurai;
	
	// Tweakable Variables
	this->size.x = 66;
	this->size.y = 62;
}

Samurai::~Samurai() {

}

void Samurai::update(const sf::Time &deltaTime) {

}