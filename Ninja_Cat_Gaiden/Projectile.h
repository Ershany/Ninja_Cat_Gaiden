#pragma once

#include <SFML\Graphics.hpp>

#include "Updateable.h"
#include "Renderable.h"
#include "GamestateManager.h"

class Projectile : public Updateable, public Renderable {
public:
	enum Type { Shuriken, Smokebomb };

	Projectile(sf::Vector2f &position, sf::Vector2u &size, sf::Vector2f &velocity, GamestateManager &gsm, Type type, sf::Vector2f &velocityDrag = sf::Vector2f(1.0f, 1.0f));
	~Projectile();

	void update(const sf::Time &deltaTime) override;
	void move(float x, float y);

	bool shouldRemove;
	sf::Vector2f collisionPoints[4]; // Used for collision detection
	Type type;
private:
	void updateCollisionPoints();

	GamestateManager &gsm;

	sf::Vector2u size;
	sf::Vector2f velocity;
	sf::Vector2f velocityDrag;

	int collisionTune;
};