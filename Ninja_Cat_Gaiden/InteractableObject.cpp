#include "InteractableObject.h"

InteractableObject::InteractableObject(sf::Vector2f &position, GamestateManager &gsm) 
	: gsm(gsm)
{
	this->position = position;
	this->shouldRemove = false;
	this->activated = false;
}

InteractableObject::~InteractableObject() {

}