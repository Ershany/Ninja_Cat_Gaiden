#include "ExitPortal.h"
#include "Defs.h"

#include <iostream>

ExitPortal::ExitPortal(sf::Vector2f &position, GamestateManager &gsm, Player *player)
	: InteractableObject(position, gsm), CollectibleObject(position, sf::Vector2u(32, 32), player)
{
	this->type = InteractableObject::Type::ExitPortal;

	// Tweakable Variables
	this->maxGrabLength = 40.0f * 40.0f; // The distance (radius) at which the player can grab the object (Note: Square it since the calucation doesnt sqrt)
}

ExitPortal::~ExitPortal() {

}

void ExitPortal::update(const sf::Time &deltaTime) {

}

void ExitPortal::action(const sf::Time &deltaTime) {
	
}