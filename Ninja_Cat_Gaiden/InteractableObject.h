#pragma once

#include <SFML\Graphics.hpp>

#include "GamestateManager.h"
#include "Updateable.h"
#include "Renderable.h"

class InteractableObject : public Updateable, public Renderable {
public:
	enum Type { Chandelier, Smoke, Hideable, ScrapMetal, Container, Chemical };

	InteractableObject(sf::Vector2f &position, GamestateManager &gsm);
	virtual ~InteractableObject();

	virtual void update(const sf::Time &deltaTime) = 0;
	virtual void action(const sf::Time &deltaTime) = 0;


	bool shouldRemove;
	bool activated;
	Type type;
protected:
	GamestateManager &gsm;
};